#include <ftul/dynamic_linking.h>

#include <stdlib.h>

namespace Fractal {

    DynamicLibrary::DynamicLibrary() : _loaded(false) {
        #ifdef FRACTAL_PLATFORM_UNIX
        _handle = nullptr;
        #elif defined(FRACTAL_PLATFORM_WINDOWS)
        _handle = nullptr; 
        #endif
    }


    DynamicLibrary::DynamicLibrary(const char* path) : _loaded(false) {
        open(path);
    }

    void DynamicLibrary::open(const char* path) {
        if(_loaded) {
            fractal_abort(); // if we are reloading with the same library, this needs to be dealt with
        }

        #ifdef FRACTAL_PLATFORM_UNIX
        _handle = dlopen(path, RTLD_LAZY);
        #elif defined(FRACTAL_PLATFORM_WINDOWS)
        _handle = LoadLibraryA(path); 
        #endif

        if(_handle) {
            _loaded = true;
        }
    }

    void DynamicLibrary::close() {
        if(!_loaded) {
            return;
        }

        #ifdef FRACTAL_PLATFORM_UNIX
        dlclose(_handle);
        #elif defined(FRACTAL_PLATFORM_WINDOWS)
        FreeLibrary(_handle); 
        #endif

        _loaded = false;
    }

    bool DynamicLibrary::is_loaded() const {
        return _loaded;
    }

    void* DynamicLibrary::find_function(const char* name) {
        #ifdef FRACTAL_PLATFORM_UNIX
        return dlsym(_handle, name);
        #elif defined(FRACTAL_PLATFORM_WINDOWS)
        return (void*)GetProcAddress(_handle, name);
        #endif
    }

}