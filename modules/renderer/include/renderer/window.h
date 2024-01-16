#ifndef FRACTAL_RENDERER_WINDOW_H
#define FRACTAL_RENDERER_WINDOW_H

#include <ftul/engine_core.h>
#include <ftul/event_system.h>
#include <ftul/fractal_common.h>

#include <SDL2/SDL.h>

namespace Fractal {

    class Window {
    public:
        Window();

        void fetch_event_buses(Reference<EngineSharedResources> esr);

        void open(const char *title, int x, int y, int w, int h, uint32_t flags);
        void close();

        void poll_events();
        bool should_close();

        SDL_Window* get_handle();
    private:
        SDL_Window* _handle;
        int _width, _height;

        bool _should_close;

        Reference<EventBus> _shutdown_bus;

        class WindowEventHandler : public EventSubscriber {
        public:
            WindowEventHandler(bool* loc);
            ~WindowEventHandler() override;

            void handle_event(Reference<Event> ignored) override;
        private:
            bool* _write_location;
        };

        Reference<WindowEventHandler> _window_event_handler;
    };

}

#endif