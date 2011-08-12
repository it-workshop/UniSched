#include <event.h>

Event::Event(unsigned long long int id, string name, time_t begin, time_t end, string description)
{
    people_ = new Group (2 * id + 1, "", "group of event: " + name);
    id_ = id;
    description_ = description;
    name_ = name;
    begin_ = begin;
    end_ = end;
}

Event::~Event()
{
    delete people_;
}

unsigned long long int Event::get_id()
{
    return id_;
}

string Event::get_name()
{
    return name_;
}

string Event::get_description()
{
    return description_;
}

time_t Event::get_begin()
{
    return begin_;
}

time_t Event::get_end()
{
    return end_;
}

Group *Event::get_group()
{
    return people_;
}

vector<Calendar*> *Event::get_related_calendars()
{
    return &related_calendars_;
}

void Event::add_related_calendar(Calendar *adding)
{
    related_calendars_.push_back(adding);
}

void Event::delete_related_calendar(Calendar *deleting)
{
    for (vector<Calendar*>::iterator it = related_calendars_.begin(); it != related_calendars_.end(); it ++)
        if (*it == deleting)
        {
            it = related_calendars_.erase(it);
            break;
        }
}

void Event::add_person(Person *adding, string status)
{
    people_->add_person(adding, status);
}

void Event::delete_person(Person *deleting)
{
    people_->delete_person(deleting);
}

