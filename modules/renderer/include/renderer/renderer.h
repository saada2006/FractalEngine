#ifndef FRACTAL_RENDERER_GLRENDERER_H
#define FRACTAL_RENDERER_GLRENDERER_H

#include <renderer/context.h>

#include <ftul/engine_core.h>
#include <ftul/reference.h>

namespace Fractal {

    class Renderer { 
    public:
        void init(Reference<EngineSharedResources> esr);
        void quit();

        void run_main_loop();
    private: 
        Reference<Context> _ctx;
    };

};

#endif