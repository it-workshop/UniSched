#include <calendar.h>

Calendar::Calendar(std::string id, std::string name)
{
    id_ = id;
    name_ = name;
}

Calendar::Calendar(Calendar *calendar)
{
    id_ = calendar->id_;
    name_ = calendar->name_;
    for (std::vector<Event*>::iterator it = calendar->events_.begin(); it != calendar->events_.end(); it ++)
        events_.push_back(*it);
}

Calendar::~Calendar(void)
{
}

std::vector<Event*> *Calendar::get_events(void)
{
    return &events_;
}

std::string Calendar::get_id(void)
{
    return id_;
}

std::string Calendar::get_name(void)
{
    return name_;
}

void Calendar::merge_calendar(Calendar *adding)
{
    for (std::vector<Event*>::iterator it = adding->get_events()->begin(); it != adding->get_events()->end(); it ++)
        add_event_nocollision(*it);
}

bool Calendar::has_event(Event *event)
{
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == event)
            return true;
    return false;
}

void Calendar::add_event_nocollision(Event *adding)
{
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == adding)
            return;
    add_event(adding);
}

void Calendar::add_event(Event *adding)
{
    adding->add_use(this);
    events_.push_back(adding);
}

void Calendar::delete_event(Event *deleting)
{
    deleting->delete_use(this);
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if (*it == deleting)
        {
            it = events_.erase(it);
            break;
        }
}

