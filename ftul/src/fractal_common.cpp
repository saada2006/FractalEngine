#include <ftul/fractal_common.h>

#include <stdlib.h>

#include <iostream>

namespace Fractal {

    void init_ftul() {
        std::cout << "FTUL is now intialized!\n";
    }

    void fractal_abort() {
        abort();
    }

    void fractal_exit(int code) {
        exit(code);
    }

}