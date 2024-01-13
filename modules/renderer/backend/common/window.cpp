#include "renderer/window.h"

namespace Fractal {

    void Window::open(const char *title, int x, int y, int w, int h, uint32_t flags) {
        SDL_Init(SDL_INIT_VIDEO);

        _handle = SDL_CreateWindow(title, x, y, w, h, flags);
    }

    void Window::close() {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

}