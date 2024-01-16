#ifndef FRACTAL_RENDERER_GLRENDERER_H
#define FRACTAL_RENDERER_GLRENDERER_H

#include <renderer/window_base.h>

#include <fsl/common.h>

namespace Fractal {

    class Renderer { 
    public:
        void init(Reference<EngineSharedResources> esr);
        void quit();

        void run_main_loop();
    private: 
        Reference<IWindow> _window;
    };

};

#endif