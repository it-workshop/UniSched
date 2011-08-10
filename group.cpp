#include <group.h>

Group::Group(std::string id, std::string name, std::string description)
{
    id_ = id;
    name_ = name;
    description_ = description;
    calendar_ = new Calendar('c' + id, "");
}

Group::~Group(void)
{
    delete calendar_;
}

std::string Group::get_name(void)
{
    return name_;
}

std::string Group::get_id(void)
{
    return id_;
}

std::string Group::get_description(void)
{
    return description_;
}

Calendar *Group::get_calendar(void)
{
    return calendar_;
}

std::vector<Person*> *Group::get_people(void)
{
    return &people_;
}

void Group::merge_group(Group *adding)
{
    for (std::vector<Person*>::iterator it = adding->get_people()->begin(); it != adding->get_people()->end(); it ++)
        add_person_nocollision(*it);
}

void Group::add_person_nocollision(Person *adding)
{
    for (std::vector<Person*>::iterator it = people_.begin(); it != people_.end(); it ++)
        if ((*it) == adding)
            return;
    add_person(adding);
}


void Group::add_event(Event *adding)
{
    calendar_->add_event(adding);
}

void Group::delete_event(Event *deleting)
{
    calendar_->delete_event(deleting);
}

void Group::add_person(Person *adding)
{
    adding->get_calendar()->merge_calendar(calendar_);
    adding->add_group(this);
    people_.push_back(adding);
}

void Group::delete_person(Person *deleting)
{
    deleting->delete_group(this);
    for (std::vector<Person*>::iterator it = people_.begin(); it != people_.end(); it ++)
        if (*it == deleting)
        {
            it = people_.erase(it);
            break;
        }
}

