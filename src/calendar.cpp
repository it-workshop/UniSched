#include <calendar.h>

Calendar::Calendar(unsigned long long int id)
{
    id_ = id;
}

Calendar::Calendar(unsigned long long int id, Calendar *calendar)
{
    id_ = id;
    for (std::vector<Event*>::iterator it = calendar->events_.begin(); it != calendar->events_.end(); it ++)
        events_.push_back(*it);
}

Calendar::~Calendar()
{
    for (std::vector<Event *>::iterator it = events_.begin(); it != events_.end(); it ++)
        delete_event(*it);
}

std::vector<Event*> *Calendar::get_events()
{
    return &events_;
}

unsigned long long int Calendar::get_id()
{
    return id_;
}

void Calendar::merge_calendar(Calendar *adding)
{
    for (std::vector<Event *>::iterator it = adding->get_events()->begin(); it != adding->get_events()->end(); it ++)
        add_event(*it);
}

bool Calendar::has_event(Event *event)
{
    for (std::vector<Event *>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == event)
            return true;
    return false;
}

void Calendar::add_event(Event *adding)
{
    for (std::vector<Event *>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == adding)
            return;
    
    adding->add_related_calendar(this);
    events_.push_back(adding);
}

void Calendar::delete_event(Event *deleting)
{
    deleting->delete_related_calendar(this);
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if (*it == deleting)
        {
            it = events_.erase(it);
            break;
        }
}

