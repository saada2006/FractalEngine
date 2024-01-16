#include <renderer/context.h>
#include <renderer/window.h>

#include <GL/glew.h>

#include <ftul/logging.h>

#include <sstream>

namespace Fractal {

    class GLContext : public Context {
    public:
        GLContext(Reference<EngineSharedResources> esr) {
            _swap_chain_update = esr->_common_buses.core.swap_chain_update;

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            _window.open("Fractal Process", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
            _window.fetch_event_buses(esr);

            _native_context = SDL_GL_CreateContext(_window.get_handle());
            
            if(glewInit() != GLEW_OK) {
                write_log("Failed to initialize GLEW!", FRACTAL_LOG_ABORT);
            } else {

                std::stringstream builder;

                builder << "OpenGL context successfuly created with the following properties:\n"
                        << "\tGPU Vendor:\t" << glGetString(GL_VENDOR) << "\n"
                        << "\tGPU Renderer:\t" << glGetString(GL_RENDERER) << "\n"
                        << "\tOpenGL Version:\t" << glGetString(GL_VERSION) << "\n"
                        << "\tGLSL Version:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION);

                write_log(builder.str());
            }

        }

        virtual void destroy() override {
            SDL_GL_DeleteContext(_native_context);
            _window.close();
        }

        bool alive() override {
            return !_window.should_close();
        }

        void update() override {
            SDL_GL_SwapWindow(_window.get_handle());
            // send swap chain update
            _swap_chain_update->publish(nullptr);
        }

        void clear(float r, float g, float b, float a) override {
            float color[] = {r, g, b, a};
            glClearBufferfv(GL_COLOR, 0, color);
        }
    private:
        Window _window;
        SDL_GLContext _native_context;

        Reference<EventBus> _swap_chain_update;
    };

    Reference<Context> create_context(Reference<EngineSharedResources> esr) {
        return std::make_shared<GLContext>(esr);
    }

}