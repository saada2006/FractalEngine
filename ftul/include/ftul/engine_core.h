#ifndef FTUL_ENGINE_CORE_H
#define FTUL_ENGINE_CORE_H

#include "event_system.h"

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