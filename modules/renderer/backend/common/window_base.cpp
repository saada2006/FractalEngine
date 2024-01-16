#include <renderer/window_base.h>

#include <ftul/logging.h>

namespace Fractal {

    IWindow::IWindow(Reference<EngineSharedResources> esr) : _should_close(true) {
        _shutdown_bus = esr->_common_buses.core.shutdown;
        _swap_chain_update = esr->_common_buses.core.swap_chain_update;

        _window_event_handler = std::make_shared<WindowEventHandler>(&_should_close);
        _shutdown_bus->subscribe(_window_event_handler);

    }

    void IWindow::open(const char *title, int w, int h) {
        SDL_Init(SDL_INIT_VIDEO);

        uint32_t flags = SDL_WINDOW_SHOWN;

        flags |= get_context_creation_flags();

        _window_handle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
        _should_close = false;

        create_context();
    }

    void IWindow::close() {
        destroy_context();

        SDL_DestroyWindow(_window_handle);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

    bool IWindow::should_close() {
        return _should_close;
    }

    void IWindow::update() {
        present();
        // send swap chain update
        _swap_chain_update->publish(nullptr);
    }

    SDL_Window* IWindow::get_handle() {
        return _window_handle;
    }

    IWindow::WindowEventHandler::WindowEventHandler(bool* loc) : _write_location(loc) {}
    IWindow::WindowEventHandler::~WindowEventHandler() {}

    void IWindow::WindowEventHandler::handle_event(Reference<IEvent> ignored) {
        *_write_location = true;
    }


}