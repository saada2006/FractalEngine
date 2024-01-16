#ifndef FTUL_EVENT_SYSTEM_H
#define FTUL_EVENT_SYSTEM_H

#include "fractal_common.h"
#include "reference.h"

#include <map> 
#include <string>
#include <vector>

namespace Fractal {

    class EventBus;

    // raw event - only contains metadata
    // we'll make the event system more efficient later
    struct Event {
        virtual ~Event() = delete;

        Reference<EventBus> _bus;
    };

    class EventSubscriber {
    public:
        virtual ~EventSubscriber();

        virtual void handle_event(Reference<Event> e) = 0;
    };

    class EventBus {
    public:
        void publish(Reference<Event> e);
        void subscribe(Reference<EventSubscriber> sub);
    private:
        std::vector<Reference<EventSubscriber>> _subscribers; // I should probably use a smart pointer for this
    };

    class EventBusMap {
    public:
        void add(const std::string& s, Reference<EventBus> bus);
        Reference<EventBus> get(const std::string& s);

        void subscribe(const std::string& s, Reference<EventSubscriber> sub);
        void publish(const std::string& s, Reference<Event> e);
    private:
        bool check_preexisting(const std::string& s);
        Reference<EventBus> get_mapping(const std::string& s);

        std::map<std::string, Reference<EventBus>> _mapping;
    };

};

#endif