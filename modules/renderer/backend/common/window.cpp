#include <renderer/window.h>

#include <ftul/logging.h>

namespace Fractal {

    Window::Window() : _should_close(true) {}

    void Window::fetch_event_buses(EventBusMap* ebm) {
        _shutdown_bus = ebm->get("core/shutdown");
    }


    void Window::open(const char *title, int x, int y, int w, int h, uint32_t flags) {
        SDL_Init(SDL_INIT_VIDEO);

        _handle = SDL_CreateWindow(title, x, y, w, h, flags);
        _should_close = false;
    }

    void Window::close() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    void Window::poll_events() {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    _should_close = true;
                    _shutdown_bus->publish(nullptr, nullptr);
                    break;
                default:
                    write_log("Unknown SDL event type! " + std::to_string(e.type), FRACTAL_LOG_DEBUG);
                    break;
            }
        }
    }

    bool Window::should_close() {
        return _should_close;
    }

    SDL_Window* Window::get_handle() {
        return _handle;
    }


}