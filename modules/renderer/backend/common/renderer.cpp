#include <renderer/renderer.h>

namespace Fractal {

    void Renderer::init() {
        _ctx = alloc_context();
        _ctx->create();
    }

    void Renderer::quit() {
        _ctx->destroy();
        free_context(_ctx);
    }

}