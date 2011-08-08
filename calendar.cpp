#include <calendar.h>

Calendar::Calendar(void)
{
}

Calendar::~Calendar(void)
{
}

std::vector<Event*> *Calendar::get_Events(void)
{
    return &events_;
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

