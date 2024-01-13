#ifndef FTUL_FRACTAL_COMMON_H
#define FTUL_FRACTAL_COMMON_H

#ifdef __unix__
#define FRACTAL_PLATFORM_UNIX
#endif

#ifdef __GNUC__

#define FRACTAL_COMPILER_GCC

#define FRACTAL_EXPORT __attribute__((visibility("default")))
#define FRACTAL_IMPORT

// solution for now
#define FRACTAL_DLFUNC FRACTAL_EXPORT

#else
#error Fractal only supported on Linux via GCC at the moment.
#endif

namespace Fractal {
    void init_ftul();

    void fractal_abort();
    void fractal_exit(int code);
}

#endif 