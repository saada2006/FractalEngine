#include <renderer/window.h>

#include <ftul/logging.h>

namespace Fractal {

    Window::Window() : _should_close(true) {
        _window_event_handler = std::make_shared<WindowEventHandler>(&_should_close);
    }

    void Window::fetch_event_buses(Reference<EngineSharedResources> esr) {
        _shutdown_bus = esr->_common_buses.core.shutdown;
        _shutdown_bus->subscribe(_window_event_handler);
    }


    void Window::open(const char *title, int x, int y, int w, int h, uint32_t flags) {
        SDL_Init(SDL_INIT_VIDEO);

        _handle = SDL_CreateWindow(title, x, y, w, h, flags);
        _should_close = false;
    }

    void Window::close() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    bool Window::should_close() {
        return _should_close;
    }

    SDL_Window* Window::get_handle() {
        return _handle;
    }

    Window::WindowEventHandler::WindowEventHandler(bool* loc) : _write_location(loc) {}
    Window::WindowEventHandler::~WindowEventHandler() {}

    void Window::WindowEventHandler::handle_event(Reference<Event> ignored) {
        *_write_location = true;
    }


}