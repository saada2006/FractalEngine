#include <renderer/renderer.h>

namespace Fractal {

    void Renderer::init(Reference<EngineSharedResources> esr) {
        _ctx = create_context(esr);
    }

    void Renderer::quit() {
        _ctx->destroy();
    }

    void Renderer::run_main_loop() {
        while(_ctx->alive()) {
            _ctx->clear(0.0, 0.0, 0.0, 1.0);

            _ctx->update();
        }
    }

}