#include <renderer/renderer_common.h>

#include <ftul/logging.h>

#include <iostream>

using namespace Fractal;

void fractal_init_module() {
    write_log("Renderer intialized!");
}

void fractal_cleanup_module() {
    write_log("Renderer cleaned up!");
}
