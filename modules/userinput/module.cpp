#include <SDL2/SDL.h>

#include <fsl/common.h>

namespace Fractal {

    class EventDemux : public IEventSubscriber {
    public:
        EventDemux(Reference<EngineSharedResources> esr) : _shutdown_bus(esr->_common_buses.core.shutdown) {}

        ~EventDemux() override {}

        void handle_event(Reference<IEvent> ignored) override {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        _shutdown_bus->publish(nullptr);
                        break;
                    default:
                        write_log("Unknown SDL event type! " + std::to_string(e.type), FRACTAL_LOG_DEBUG);
                        break;
                }
            }
        }

    private:
        Reference<EventBus> _shutdown_bus;
    };

    class UserInputModule : public IModule {
    public:
        void init(Reference<EngineSharedResources> esr) override {
            _event_demux = std::make_shared<EventDemux>(esr);
            esr->_common_buses.core.swap_chain_update->subscribe(_event_demux);
        }

        void cleanup() override {}
    private:
        Reference<EventDemux> _event_demux;
    };

    extern "C" {
        FRACTAL_EXPORT Reference<IModule> fractal_alloc_module() {
            return std::make_shared<UserInputModule>();
        }
    }

}

