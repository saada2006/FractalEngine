#ifndef FRACTAL_RENDERER_WINDOW_H
#define FRACTAL_RENDERER_WINDOW_H

#include <ftul/fractal_common.h>

#include <SDL.h>

namespace Fractal {

    enum FractalWindowingMode {
        FRACTAL_WINDOW_MODE_WINDOWED,
        FRACTAL_WINDOW_MODE_WINDOWED_FULLSCREEN,
        FRACTAL_WINDOW_MODE_FULLSCREEN
    };

    class Window {
    public:
        void open(FractalWindowingMode mode, const char* name, int width = -1, int height = -1);
        void close();

    private:
        SDL_Window* _handle;
        int _width, _height;
    };

}

#endif