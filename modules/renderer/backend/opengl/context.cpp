#include <renderer/context.h>
#include <renderer/window.h>

namespace Fractal {

    class GLContext : public Context {
    public:
        void create(EngineSharedResources* shared_resources) override {
            _window.open("Fractal Process", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
            _window.fetch_event_buses(&shared_resources->_event_bus_map);
        }

        void destroy() override {
            _window.close();
        }

        bool alive() override {
            return !_window.should_close();
        }

        void update() override {
            _window.poll_events();
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