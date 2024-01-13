#ifndef FRACTAL_RENDERER_GLRENDERER_H
#define FRACTAL_RENDERER_GLRENDERER_H

#include <renderer/context.h>

namespace Fractal {

    class Renderer {
    public:
        void init();
        void quit();
    private: 
        Context* _ctx;
    };

};

#endif