#ifndef FRACTAL_RENDERER_CONTEXT_H
#define FRACTAL_RENDERER_CONTEXT_H

#include <ftul/engine_core.h>

namespace Fractal {

    class Context {
    public:
        virtual void create(EngineSharedResources* shared_resources) = 0;
        virtual void destroy() = 0;
        virtual bool alive() = 0;
        virtual void update() = 0;
        virtual void clear(float r, float g, float b, float a) = 0;
    };

    Context* alloc_context();
    void free_context(Context* ctx);

};

#endif