#include "renderer/window.h"

namespace Fractal {

    void Window::open(FractalWindowingMode mode, const char* name, int width, int height) {
        SDL_Init(SDL_INIT_VIDEO);

        _handle = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    }

    void Window::close() {

        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

}