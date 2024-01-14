#ifndef FTUL_ENGINE_CORE_H
#define FTUL_ENGINE_CORE_H

#include "event_system.h"

namespace Fractal {

    struct EngineSharedResources {
        EventBusMap _event_bus_map;
    };

}

#endif