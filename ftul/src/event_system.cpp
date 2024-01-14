#include <ftul/event_system.h>
#include <ftul/logging.h>

namespace Fractal {

    void EventBus::publish(Event* e, EventPublisher* pub) {
        if(e)
            e->_pub = pub;

        for(auto& sub : _subscribers) {
            sub->handle_event(e);
        }

        if(pub)
            pub->retreive_event(e);
    }

    void EventBus::subscribe(EventSubscriber* sub) {
        _subscribers.push_back(sub);
    }

    void EventBusMap::add(const std::string& s, EventBus* bus) {
        if(check_preexisting(s)) {
            write_log("Event bus \"" + s + "\" already exists!", FRACTAL_LOG_ABORT);
        }

        _mapping[s] = bus;
    }

    EventBus* EventBusMap::get(const std::string& s) {
        return get_mapping(s);
    }

    void EventBusMap::subscribe(const std::string& s, EventSubscriber* sub) {
        get_mapping(s)->subscribe(sub);
    }

    void EventBusMap::publish(const std::string& s, Event* e, EventPublisher* pub) {
        get_mapping(s)->publish(e, pub);
    }
    
    bool EventBusMap::check_preexisting(const std::string& s) {
        auto iter = _mapping.find(s);

        return (iter != _mapping.end());
    }


    EventBus*& EventBusMap::get_mapping(const std::string& s) {
        if(!check_preexisting(s)) {
            write_log("Event bus \"" + s + "\" not found!", FRACTAL_LOG_ABORT);
        }

        return _mapping[s];
    }


}