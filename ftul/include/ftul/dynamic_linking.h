#ifndef FTUL_DYNAMIC_LINKING_H
#define FTUL_DYNAMIC_LINKING_H

#include "fractal_common.h"

#if defined(FRACTAL_PLATFORM_UNIX)
#include <dlfcn.h>
#elif defined(FRACTAL_PLATFORM_WINDOWS)
#include <libloaderapi.h>
#endif

namespace Fractal {

    class DynamicLibrary {
    public:
        DynamicLibrary();
        DynamicLibrary(const char* path);

        void open(const char* path);
        void close();

        bool is_loaded() const;
        void* find_function(const char* name);
    private:
        bool _loaded;

        #ifdef FRACTAL_PLATFORM_UNIX
        void* _handle;
        #elif defined(FRACTAL_PLATFORM_WINDOWS)
        HMODULE _handle; 
        #endif
    };

};

#endif