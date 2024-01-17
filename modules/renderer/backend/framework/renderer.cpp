#include <renderer/renderer.h>

namespace Fractal {

    void Renderer::init(Reference<EngineSharedResources> esr) {
        _window = create_window(esr);
        _window->open("Fractal Process", 1280, 720); 
    }

    void Renderer::quit() {
        _window->close();
    }

    void Renderer::run_main_loop() {
        while(!_window->should_close()) {
            _window->clear(0.0, 0.0, 0.0, 1.0);

            _window->update();
        }
    }

}