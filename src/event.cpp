#include <event.h>

Event::Event(unsigned long long int id, std::string name, time_t begin, time_t end, std::string description)
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

std::string Event::get_name()
{
    return name_;
}

std::string Event::get_description()
{
    return description_;
}

time_t *Event::get_begin()
{
    return &begin_;
}

time_t *Event::get_end()
{
    return &end_;
}

Group *Event::get_group()
{
    return people_;
}

std::vector<Calendar*> *Event::get_used_in()
{
    return &used_in_;
}

void Event::add_use(Calendar *adding)
{
    used_in_.push_back(adding);
}

void Event::delete_use(Calendar *deleting)
{
    for (std::vector<Calendar*>::iterator it = used_in_.begin(); it != used_in_.end(); it ++)
        if (*it == deleting)
        {
            it = used_in_.erase(it);
            break;
        }
}

void Event::add_person(Person *adding, std::string status)
{
    people_->add_person(adding, status);
}

void Event::delete_person(Person *deleting)
{
    people_->delete_person(deleting);
}

