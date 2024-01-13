#ifndef FRACTAL_RENDERER_CONTEXT_H
#define FRACTAL_RENDERER_CONTEXT_H

namespace Fractal {

    class Context {
    public:
        virtual void create() = 0;
        virtual void destroy() = 0;
    };

    Context* alloc_context();
    void free_context(Context* ctx);

};

#endif