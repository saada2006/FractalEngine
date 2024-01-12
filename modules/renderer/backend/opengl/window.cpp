#include <renderer/renderer_common.h>

#include <iostream>

namespace Fractal {

    void init_module() {
        std::cout << "Renderer intialized!\n";
    }

    void cleanup_module() {
        std::cout << "Renderer cleaned up!\n";
    }

}