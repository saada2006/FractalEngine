#include <renderer/renderer.h>
#include <renderer/module_core.h>

#include <ftul/logging.h>

using namespace Fractal;

Renderer* _renderer;

FRACTAL_EXPORT void fractal_init_module() {
    _renderer = new Renderer;
    _renderer->init();

    write_log("Renderer intialized!");
}

FRACTAL_EXPORT void fractal_cleanup_module() {
    _renderer->quit();
    delete _renderer;

    write_log("Renderer cleaned up!");
}
