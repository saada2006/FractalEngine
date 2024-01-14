#include <renderer/context.h>
#include <renderer/window.h>

#include <GL/glew.h>

#include <ftul/logging.h>

namespace Fractal {

    class GLContext : public Context {
    public:
        void create(EngineSharedResources* shared_resources) override {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            _window.open("Fractal Process", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
            _window.fetch_event_buses(&shared_resources->_event_bus_map);

            _native_context = SDL_GL_CreateContext(_window.get_handle());
            
            if(glewInit() != GLEW_OK) {
                write_log("Failed to initialize GLEW!", FRACTAL_LOG_ABORT);
            } else {
                write_log("OpenGL context successfuly created!");
            }

        }

        void destroy() override {
            _window.close();
        }

        bool alive() override {
            return !_window.should_close();
        }

        void update() override {
            SDL_GL_SwapWindow(_window.get_handle());
            _window.poll_events();
        }

        void clear(float r, float g, float b, float a) override {
            float color[] = {r, g, b, a};
            glClearBufferfv(GL_COLOR, 0, color);
        }
    private:
        Window _window;
        SDL_GLContext _native_context;
    };

    Context* alloc_context() {
        return new GLContext;
    }

    void free_context(Context* ctx) {
        delete ctx;
    }

}