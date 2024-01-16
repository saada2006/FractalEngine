#ifndef FSL_FRACTAL_H
#define FSL_FRACTAL_H

// Contains core utilities and macros

#if defined(_WIN32) 
#define FRACTAL_PLATFORM_WINDOWS  
#elif defined(__unix__)
#define FRACTAL_PLATFORM_UNIX
#endif

#ifdef __GNUC__

#define FRACTAL_COMPILER_GCC

#define FRACTAL_EXPORT __attribute__((visibility("default")))
#define FRACTAL_IMPORT

// solution for now
#define FRACTAL_DLFUNC FRACTAL_EXPORT

#else
#error Fractal only supported on GCC-based compilers at the moment.
#endif

namespace Fractal {
    void init_fsl();

    void fractal_abort();
    void fractal_exit(int code);
}

#endif