#include <ftul/fractal_common.h>

#include <ftul/dynamic_linking.h>
#include <ftul/logging.h>

#include <filesystem>
#include <iostream>
#include <vector>

using namespace Fractal;

typedef void (*ModuleProc)();

struct EngineModule {
    ModuleProc init;
    ModuleProc cleanup;
    DynamicLibrary _dynlib;
};

std::vector<EngineModule> find_all_modules() {
    std::vector<EngineModule> modules;

    auto path = std::filesystem::current_path();
    // not the best solution, but works for now
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        EngineModule mod;
        mod._dynlib.open(file.path().c_str()); // force load all files, easier than checking for dll files only

        if(!mod._dynlib.is_loaded()) {
            continue;
        }

        mod.init = (ModuleProc) mod._dynlib.find_function("fractal_init_module");
        mod.cleanup = (ModuleProc) mod._dynlib.find_function("fractal_cleanup_module");
        
        if(mod.init && mod.cleanup) {
            write_log(("Found module at " + file.path().string()).c_str());
            modules.push_back(mod);
        } 
    }

    return modules;
}

int main(int argc, char** argv) {
    auto modules = find_all_modules();

    write_log("Loading all modules...");

    for(const auto& mod : modules) {
        mod.init();
    }

    write_log("Cleaning up all modules...");

    for(const auto& mod : modules) {
        mod.cleanup();
    }

    return 0;
}