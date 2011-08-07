#include <event.h>

Event::Event(std::string name, time_t begin, time_t end)
{
    people_ = new Group (name); 
    name_ = name;
    begin_ = begin;
    end_ = end;
}

Event::~Event(void)
{
    delete people_;
}

std::string Event::get_Name(void)
{
    return name_;
}

time_t *Event::get_Begin(void)
{
    return &begin_;
}

time_t *Event::get_End(void)
{
    return &end_;
}

Group *Event::get_Group(void)
{
    return people_;
}

std::vector<Calendar*> *Event::get_Used_in(void)
{
    return &used_in_;
}

void Event::add_Use(Calendar *adding)
{
    used_in_.push_back(adding);
    adding->add_Event(this);
}

void Event::delete_Use(Calendar *deleting)
{
    for (std::vector<Calendar*>::iterator it = used_in_.begin(); it != used_in_.end(); it ++)
        if (*it == deleting)
        {
            it = used_in_.erase(it);
            break;
        }
    deleting->delete_Event(this);
}

void Event::add_Person(Person *adding)
{
    people_->add_Person(adding);
}

void Event::delete_Person(Person *deleting)
{
    people_->delete_Person(deleting);
}

