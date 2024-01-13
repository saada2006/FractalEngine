#include <ftul/fractal_common.h>
 
#include <ftul/dynamic_linking.h>
#include <ftul/logging.h>
#include <ftul/module.h>

#include <filesystem>
#include <iostream>
#include <thread>
#include <vector>

namespace Fractal {

    typedef Module* (*ModuleAllocProc)();
    typedef void (*ModuleFreeProc)(Module*);

    struct ModuleWrapper {
        Module* _module;

        ModuleAllocProc alloc_proc;
        ModuleFreeProc free_proc;
        DynamicLibrary _dynlib;
    };

    class Loader {
    public:
        void run() {
            write_log("Searching for modules...");

            find_all_modules();

            std::vector<std::thread> init_threads;
            for(auto& mod : _modules) {
                mod._module = mod.alloc_proc();
                init_threads.emplace_back(&Loader::exec_init, mod._module);
            }
            wait_for_all_threads(init_threads);

            write_log("Cleaning up all modules...");

            std::vector<std::thread> cleanup_threads;
            for(auto& mod : _modules) {
                cleanup_threads.emplace_back(&Loader::exec_cleanup, mod._module);
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
                mdl._dynlib.open(file.path().c_str()); // force load all files, easier than checking for dll files only

                if(!mdl._dynlib.is_loaded()) {
                    continue;
                }

                mdl.alloc_proc = (ModuleAllocProc) mdl._dynlib.find_function("fractal_alloc_module");
                mdl.free_proc = (ModuleFreeProc) mdl._dynlib.find_function("fractal_free_module");
                
                if(mdl.alloc_proc && mdl.free_proc) {
                    write_log(("Found module at " + file.path().string()).c_str());
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

        static void exec_init(Module* mdl) {
            mdl->init();
        }

        static void exec_cleanup(Module* mdl) {
            mdl->cleanup();
        }

        std::vector<ModuleWrapper> _modules;
    };

}


int main(int argc, char** argv) {
    Fractal::Loader loader;
    loader.run();

    return 0;
}