#include <calendar.h>

Calendar::Calendar(std::string ID, std::string name)
{
    ID_ = ID;
    name_ = name;
}

Calendar::~Calendar(void)
{
}

std::vector<Event*> *Calendar::get_Events(void)
{
    return &events_;
}

std::string Calendar::get_ID(void)
{
    return ID_;
}

std::string Calendar::get_Name(void)
{
    return name_;
}

void Calendar::merge_calendar(Calendar *adding)
{
    for (std::vector<Event*>::iterator it = adding->get_Events()->begin(); it != adding->get_Events()->end(); it ++)
        add_Event_nocollision(*it);
}

bool Calendar::has_Event(Event *event)
{
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == event)
            return true;
    return false;
}

void Calendar::add_Event_nocollision(Event *adding)
{
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if ((*it) == adding)
            return;
    add_Event(adding);
}

void Calendar::add_Event(Event *adding)
{
    events_.push_back(adding);
}

void Calendar::delete_Event(Event *deleting)
{
    for (std::vector<Event*>::iterator it = events_.begin(); it != events_.end(); it ++)
        if (*it == deleting)
        {
            it = events_.erase(it);
            break;
        }
}

