#include <event.h>

Event::Event(std::string id, std::string name, time_t begin, time_t end, std::string description)
{
    people_ = new Group ('g' + id, "", "group of event: " + name);
    id_ = id;
    description_ = description;
    name_ = name;
    begin_ = begin;
    end_ = end;
}

Event::~Event(void)
{
    delete people_;
}

std::string Event::get_id(void)
{
    return id_;
}

std::string Event::get_name(void)
{
    return name_;
}

std::string Event::get_description(void)
{
    return description_;
}

time_t *Event::get_begin(void)
{
    return &begin_;
}

time_t *Event::get_end(void)
{
    return &end_;
}

Group *Event::get_group(void)
{
    return people_;
}

std::vector<Calendar*> *Event::get_used_in(void)
{
    return &used_in_;
}

void Event::add_use(Calendar *adding)
{
    used_in_.push_back(adding);
    adding->add_event(this);
}

void Event::delete_use(Calendar *deleting)
{
    for (std::vector<Calendar*>::iterator it = used_in_.begin(); it != used_in_.end(); it ++)
        if (*it == deleting)
        {
            it = used_in_.erase(it);
            break;
        }
    deleting->delete_event(this);
}

void Event::add_person(Person *adding)
{
    people_->add_person(adding);
}

void Event::delete_person(Person *deleting)
{
    people_->delete_person(deleting);
}

