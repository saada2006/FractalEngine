#include <fsl/engine_core.h>

namespace Fractal {

    EngineSharedResources::EngineSharedResources() {
        #define CREATE_EVENT_BUS(EBUS_NAME) \
            _common_buses.EBUS_NAME = std::make_shared<EventBus>(); \
            _event_bus_map.add(#EBUS_NAME, _common_buses.EBUS_NAME); 


        CREATE_EVENT_BUS(core.shutdown);
        CREATE_EVENT_BUS(core.swap_chain_update);


        #undef CREATE_EVENT_BUS
    }

}