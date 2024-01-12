#ifndef FTUL_DYNAMIC_LINKING_H
#define FTUL_DYNAMIC_LINKING_H

#include "fractal_common.h"

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
        #else 
        #error Dynamic linking is not yet implemented for the current platform!
        #endif
    };

};

#endif