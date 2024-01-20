#ifndef FSL_MODULE_H
#define FSL_MODULE_H

#include "engine_core.h"

namespace Fractal {

    class IModule {
    public:
        virtual void init(Reference<EngineSharedResources> esr) = 0;
        virtual void cleanup() = 0;

        virtual ~IModule();
    };

}

#endif