#ifndef FSL_ENGINE_CORE_H
#define FSL_ENGINE_CORE_H

#include "event_system.h"
#include "fractal.h"

namespace Fractal {

    struct EngineSharedResources {
        EngineSharedResources();

        EventBusMap _event_bus_map;

        struct {
            
            struct {
                Reference<EventBus> shutdown;
                Reference<EventBus> swap_chain_update;
            } core;

        } _common_buses;
    };

}

#endif