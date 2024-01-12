#include <ftul/fractal_common.h>

#include <filesystem>
#include <iostream>
#include <vector>

#include <dlfcn.h>

typedef void (*ModuleProc)();

struct EngineModule {
    ModuleProc init;
    ModuleProc cleanup;
    void* addr;
};

std::vector<EngineModule> find_all_modules() {
    std::vector<EngineModule> modules;

    auto path = std::filesystem::current_path();
    for (const auto& file : std::filesystem::directory_iterator(path)) {
        auto libaddr = dlopen(file.path().c_str(), RTLD_NOW);

        if(!libaddr) {
            continue;
        }

        EngineModule cur_module;

        cur_module.init = (ModuleProc) dlsym(libaddr, "fractal_init_module");
        cur_module.cleanup = (ModuleProc) dlsym(libaddr, "fractal_cleanup_module");
        
        if(cur_module.init && cur_module.cleanup) {
            std::cout << "Found module at " << file.path().c_str() << '\n';
            modules.push_back(cur_module);
        }
    }

    return modules;
}

int main(int argc, char** argv) {
    auto modules = find_all_modules();

    std::cout << "Loading all modules...\n";

    for(const auto& mod : modules) {
        mod.init();
    }

    std::cout << "Cleaning up all modules...\n";

    for(const auto& mod : modules) {
        mod.cleanup();
    }

    return 0;
}