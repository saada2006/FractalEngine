#ifndef FRACTAL_RENDERER_WINDOW_H
#define FRACTAL_RENDERER_WINDOW_H

#include <ftul/engine_core.h>
#include <ftul/event_system.h>
#include <ftul/fractal_common.h>

#include <SDL2/SDL.h>

namespace Fractal {

    class IWindow {
    public:
        IWindow(Reference<EngineSharedResources> esr);

        void open(const char *title, int x, int y, int w, int h);
        void close();

        bool should_close();

        void update();
        virtual void clear(float r, float g, float b, float a) = 0;

        SDL_Window* get_handle();
    protected:
        virtual uint32_t get_context_creation_flags() = 0;
        virtual void create_context() = 0;
        virtual void destroy_context() = 0;

        virtual void present() = 0;

        SDL_Window* _window_handle;
        int _width, _height;

        bool _should_close;

        Reference<EventBus> _shutdown_bus;
        Reference<EventBus> _swap_chain_update;

        class WindowEventHandler : public IEventSubscriber {
        public:
            WindowEventHandler(bool* loc);
            ~WindowEventHandler() override;

            void handle_event(Reference<IEvent> ignored) override;
        private:
            bool* _write_location;
        };

        Reference<WindowEventHandler> _window_event_handler;
    };

    extern Reference<IWindow> create_window(Reference<EngineSharedResources> esr);

}

#endif