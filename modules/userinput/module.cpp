#include <ftul/fractal_common.h>
#include <ftul/logging.h>
#include <ftul/module.h>

#include <SDL2/SDL.h>

namespace Fractal {

    class EventDemux : public EventSubscriber {
    public:
        EventDemux(Reference<EngineSharedResources> esr) : _shutdown_bus(esr->_common_buses.core.shutdown) {}

        ~EventDemux() override {}

        void handle_event(Reference<Event> ignored) override {
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

    class UserInputModule : public Module {
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
        FRACTAL_EXPORT Reference<Module> fractal_alloc_module() {
            return std::make_shared<UserInputModule>();
        }
    }

}

