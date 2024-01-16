#include <renderer/context.h>
#include <renderer/window_base.h>

#include <GL/glew.h>

#include <ftul/logging.h>

#include <sstream>

namespace Fractal {

    class GLWindow : public IWindow {
    public:
        GLWindow(Reference<EngineSharedResources> esr) : IWindow(esr) {}

        void clear(float r, float g, float b, float a) override {
            float color[] = {r, g, b, a};
            glClearBufferfv(GL_COLOR, 0, color);
        }
    protected:
        uint32_t get_context_creation_flags() override {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            return SDL_WINDOW_OPENGL;
        }

        void create_context() override {
            _context_handle = SDL_GL_CreateContext(_window_handle);
            
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

        void destroy_context() override {
            SDL_GL_DeleteContext(_context_handle);
        }

        void present() override {
            SDL_GL_SwapWindow(_window_handle);
        }

        SDL_GLContext _context_handle;
    };

    Reference<IWindow> create_window(Reference<EngineSharedResources> esr) {
        return std::make_shared<GLWindow>(esr);
    }

}