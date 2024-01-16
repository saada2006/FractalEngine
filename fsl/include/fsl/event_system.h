#ifndef FSL_EVENT_SYSTEM_H
#define FSL_EVENT_SYSTEM_H

#include "fractal.h"
#include "reference.h"
#include "std.h"

namespace Fractal {

    class EventBus;

    // raw event - only contains metadata
    // we'll make the event system more efficient later
    struct IEvent {
        virtual ~IEvent() = delete;

        Reference<EventBus> _bus;
    };

    class IEventSubscriber {
    public:
        virtual ~IEventSubscriber();

        virtual void handle_event(Reference<IEvent> e) = 0;
    };

    class EventBus {
    public:
        void publish(Reference<IEvent> e);
        void subscribe(Reference<IEventSubscriber> sub);
    private:
        std::vector<Reference<IEventSubscriber>> _subscribers; // I should probably use a smart pointer for this
    };

    class EventBusMap {
    public:
        void add(const std::string& s, Reference<EventBus> bus);
        Reference<EventBus> get(const std::string& s);

        void subscribe(const std::string& s, Reference<IEventSubscriber> sub);
        void publish(const std::string& s, Reference<IEvent> e);
    private:
        bool check_preexisting(const std::string& s);
        Reference<EventBus> get_mapping(const std::string& s);

        std::map<std::string, Reference<EventBus>> _mapping;
    };

};

#endif