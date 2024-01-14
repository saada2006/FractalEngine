#ifndef FRACTAL_RENDERER_GLRENDERER_H
#define FRACTAL_RENDERER_GLRENDERER_H

#include <renderer/context.h>

#include <ftul/engine_core.h>

namespace Fractal {

    class Renderer {
    public:
        void init(EngineSharedResources* shared_resources);
        void quit();

        void run_main_loop();
    private: 
        Context* _ctx;
    };

};

#endif