#include <ftul/fractal_common.h>
 
#include <ftul/dynamic_linking.h>
#include <ftul/logging.h>
#include <ftul/module.h>

#include <filesystem>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace Fractal {

    typedef Reference<Module> (*ModuleAllocProc)();

    struct ModuleWrapper {
        Reference<Module> _module;
        DynamicLibrary _dynlib;
    };

    class LoaderShutdownNotifier : public EventSubscriber {
    public:
        LoaderShutdownNotifier(std::mutex* mtx) : _notif(mtx) {
            _notif->lock();
        }

        ~LoaderShutdownNotifier() override {}

        void handle_event(Reference<Event> e) override {
            _notif->unlock();
        }
    private:
        std::mutex* _notif;
    };

    class Loader {
    public:
        void run() {
            init_ftul();

            std::mutex shutdown_blocker;

            _esr = std::make_shared<EngineSharedResources>();

            _esr->_common_buses.core.shutdown->subscribe(std::make_shared<LoaderShutdownNotifier>(&shutdown_blocker));

            write_log("Searching for modules...");

            find_all_modules();

            std::vector<std::thread> init_threads;
            for(auto& mod : _modules) {
                init_threads.emplace_back(&Loader::exec_init, this, mod._module);
            }

            shutdown_blocker.lock();
            shutdown_blocker.unlock();

            wait_for_all_threads(init_threads);

            write_log("Cleaning up all modules...");
            std::vector<std::thread> cleanup_threads;
            for(auto& mod : _modules) {
                cleanup_threads.emplace_back(&Loader::exec_cleanup, this, mod._module);
            }
            wait_for_all_threads(cleanup_threads);

            free_loader_resources();
        }
    private:
        void find_all_modules() {
            auto path = std::filesystem::current_path();
            // not the best solution, but works for now
            for (const auto& file : std::filesystem::directory_iterator(path)) {
                ModuleWrapper mdl;

                mdl._dynlib.open(file.path().generic_string().c_str()); // force load all files, easier than checking for dll files only

                if(!mdl._dynlib.is_loaded()) {
                    continue;
                }

                ModuleAllocProc mod_alloc = (ModuleAllocProc) mdl._dynlib.find_function("fractal_alloc_module");
                
                if(mod_alloc) {
                    write_log(("Found module at " + file.path().string()).c_str());

                    mdl._module = mod_alloc();
                    _modules.push_back(mdl);
                } 
            }
        }

        void free_loader_resources() {
            for(auto& mdl : _modules) {
                mdl._dynlib.close();
            }
        }

        static void wait_for_all_threads(std::vector<std::thread>& threads) {
            for(auto& t : threads) {
                t.join();
            }
        }

        void exec_init(Reference<Module> mdl) {
            mdl->init(_esr);
        }

        void exec_cleanup(Reference<Module> mdl) {
            mdl->cleanup();
        }

        std::vector<ModuleWrapper> _modules;
        Reference<EngineSharedResources> _esr;
    };

}

int main(int argc, char** argv) {
    Fractal::Loader loader;
    loader.run();
    return 0;
}