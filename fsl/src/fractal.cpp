#include <fsl/fractal.h>
#include <fsl/logging.h>
#include <fsl/std.h>

namespace Fractal {

    void init_fsl() {
        write_log("FTUL is now initialized!");
    }

    void fractal_abort() {
        std::abort();
    }

    void fractal_exit(int code) {
        std::exit(code);
    }

}