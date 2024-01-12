#include <ftul/fractal_common.h>

#include <ftul/logging.h>

#include <stdlib.h>

#include <iostream>

namespace Fractal {

    void init_ftul() {
        write_log("FTUL is now initialized!");
    }

    void fractal_abort() {
        abort();
    }

    void fractal_exit(int code) {
        exit(code);
    }

}