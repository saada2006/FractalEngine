#ifndef FTUL_MODULE_H
#define FTUL_MODULE_H

#include "engine_core.h"

namespace Fractal {

    class Module {
    public:
        virtual void init(Reference<EngineSharedResources> esr) = 0;
        virtual void cleanup() = 0;
    };

}

#endif