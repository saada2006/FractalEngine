#include <ftul/event_system.h>
#include <ftul/logging.h>

namespace Fractal {

    IEventSubscriber::~IEventSubscriber() {}

    void EventBus::publish(Reference<IEvent> e) {
        for(auto& sub : _subscribers) {
            sub->handle_event(e);
        }
    }

    void EventBus::subscribe(Reference<IEventSubscriber> sub) {
        _subscribers.push_back(sub);
    }

    void EventBusMap::add(const std::string& s, Reference<EventBus> bus) {
        if(check_preexisting(s)) {
            write_log("Event bus \"" + s + "\" already exists!", FRACTAL_LOG_ABORT);
        }

        _mapping[s] = bus;
    }

    Reference<EventBus> EventBusMap::get(const std::string& s) {
        return get_mapping(s);
    }

    void EventBusMap::subscribe(const std::string& s, Reference<IEventSubscriber> sub) {
        get_mapping(s)->subscribe(sub);
    }

    void EventBusMap::publish(const std::string& s, Reference<IEvent> e) {
        get_mapping(s)->publish(e);
    }
    
    bool EventBusMap::check_preexisting(const std::string& s) {
        auto iter = _mapping.find(s);

        return (iter != _mapping.end());
    }


    Reference<EventBus> EventBusMap::get_mapping(const std::string& s) {
        if(!check_preexisting(s)) {
            write_log("Event bus \"" + s + "\" not found!", FRACTAL_LOG_ABORT);
        }

        return _mapping[s];
    }


}