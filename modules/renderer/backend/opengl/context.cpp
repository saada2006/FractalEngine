#include <renderer/context.h>
#include <renderer/window.h>

namespace Fractal {

    class GLContext : public Context {
    public:
        void create() override {
            _window.open("Fractal Process", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
        }

        void destroy() override {
            _window.close();
        }

    private:
        Window _window;
    };

    Context* alloc_context() {
        return new GLContext;
    }

    void free_context(Context* ctx) {
        delete ctx;
    }

}