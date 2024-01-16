#ifndef FRACTAL_RENDERER_CONTEXT_H
#define FRACTAL_RENDERER_CONTEXT_H

#include <fsl/common.h>

namespace Fractal {

    class Context {
    public:
        virtual void destroy() = 0;

        virtual bool alive() = 0;
        virtual void update() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
    };

    Reference<Context> create_context(Reference<EngineSharedResources> esr);

};

#endif