#ifndef FTUL_EVENT_SYSTEM_H
#define FTUL_EVENT_SYSTEM_H

#include "fractal_common.h"

#include <map>
#include <string>
#include <vector>

namespace Fractal {

    class EventBus;
    class EventPublisher;

    // raw event - only contains metadata
    // we'll make the event system more efficient later
    struct Event {
        virtual ~Event() = 0;

        EventBus* _bus;
        EventPublisher* _pub;
    };

    class EventSubscriber {
    public:
        virtual void handle_event(Event* e) = 0;
    };

    class EventPublisher {
    public:
        virtual void retreive_event(Event* e) = 0; // handle deallocation 
    };

    class EventBus {
    public:
        void publish(Event* e, EventPublisher* pub);
        void subscribe(EventSubscriber* sub);
    private:
        std::vector<EventSubscriber*> _subscribers; // I should probably use a smart pointer for this
    };

    class EventBusMap {
    public:
        void add(const std::string& s, EventBus* bus);
        EventBus* get(const std::string& s);

        void subscribe(const std::string& s, EventSubscriber* sub);
        void publish(const std::string& s, Event* e, EventPublisher* pub);
    private:
        bool check_preexisting(const std::string& s);
        EventBus*& get_mapping(const std::string& s);

        std::map<std::string, EventBus*> _mapping;
    };

};

#endif