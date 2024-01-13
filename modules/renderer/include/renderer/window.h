#ifndef FRACTAL_RENDERER_WINDOW_H
#define FRACTAL_RENDERER_WINDOW_H

#include <ftul/fractal_common.h>

#include <SDL.h>

namespace Fractal {

    class Window {
    public:
        void open(const char *title, int x, int y, int w, int h, uint32_t flags);
        void close();

    private:
        SDL_Window* _handle;
        int _width, _height;
    };

}

#endif