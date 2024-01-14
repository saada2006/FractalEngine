#include <renderer/renderer.h>

namespace Fractal {

    void Renderer::init(EngineSharedResources* shared_resources) {
        _ctx = alloc_context();
        _ctx->create(shared_resources);
    }

    void Renderer::quit() {
        _ctx->destroy();
        free_context(_ctx);
    }

    void Renderer::run_main_loop() {
        while(_ctx->alive()) {
            _ctx->clear(0.0, 0.0, 0.0, 1.0);

            _ctx->update();
        }
    }

}