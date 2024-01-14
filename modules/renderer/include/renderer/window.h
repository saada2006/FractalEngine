#ifndef FRACTAL_RENDERER_WINDOW_H
#define FRACTAL_RENDERER_WINDOW_H

#include <ftul/event_system.h>
#include <ftul/fractal_common.h>

#include <SDL.h>

namespace Fractal {

    class Window {
    public:
        Window();

        void fetch_event_buses(EventBusMap* ebm);

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
    };

}

#endif