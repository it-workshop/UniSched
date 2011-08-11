#include <group.h>

Group::Group(unsigned long long int id, std::string name, std::string description)
{
    id_ = id;
    name_ = name;
    description_ = description;
    calendar_ = new Calendar(3 * id + 2, "");
}

Group::Group(unsigned long long int id, Group *group)
{
    id_ = id;
    name_ = group->name_;
    description_ = group->description_;
    calendar_ = new Calendar(3 * id + 2, group->calendar_);
    for (std::vector<Group_Content*>::iterator it = group->people_.begin(); it != group->people_.end(); it ++)
    {
        Group_Content *a = new Group_Content();
        a->group = this;
        a->person = (*it)->person;
        a->status = (*it)->status;
        people_.push_back(a);
    }
}

Group::~Group()
{
    for (std::vector<Group_Content *>::iterator it = people_.begin(); it != people_.end(); it ++)
        delete_person((*it)->person);
    delete calendar_;
}

std::string Group::get_name()
{
    return name_;
}

unsigned long long int Group::get_id()
{
    return id_;
}

std::string Group::get_description()
{
    return description_;
}

Calendar *Group::get_calendar()
{
    return calendar_;
}

std::vector<Group_Content*> *Group::get_people()
{
    return &people_;
}

void Group::merge_group(Group *operating)
{
    for (std::vector<Group_Content*>::iterator it = operating->get_people()->begin(); it != operating->get_people()->end(); it ++)
        add_person_nocollision((*it)->person, (*it)->status);
}

void Group::exclude_group(Group *operating)
{
    for (std::vector<Group_Content*>::iterator it = operating->get_people()->begin(); it != operating->get_people()->end(); it ++)
        delete_person((*it)->person);
}

void Group::include_group(Group *operating)
{
    std::vector<Group_Content*>::iterator tmp;
    for (std::vector<Group_Content*>::iterator it0 = people_.begin(); it0 != people_.end(); it0 ++)
    {
        for (std::vector<Group_Content*>::iterator it1 = operating->get_people()->begin(); it1 != operating->get_people()->end(); it1 ++)
            if ((*it0)->person == (*it1)->person)
                goto label;
        tmp = it0;
        it0 = people_.erase(it0);
        if (tmp == people_.end())
            return;
        label:;
    }
}

void Group::add_person_nocollision(Person *adding, std::string status)
{
    for (std::vector<Group_Content*>::iterator it = people_.begin(); it != people_.end(); it ++)
        if ((*it)->person == adding)
            return;
    add_person(adding, status);
}


void Group::add_event(Event *adding)
{
    calendar_->add_event(adding);
}

void Group::delete_event(Event *deleting)
{
    calendar_->delete_event(deleting);
}

void Group::add_person(Person *adding, std::string status)
{
    adding->get_calendar()->merge_calendar(calendar_);
    Group_Content *a = new Group_Content ();
    a->group = this;
    a->person = adding;
    a->status = status;
    people_.push_back(a);
    adding->add_group(a);
}

void Group::delete_person(Person *deleting)
{
    deleting->delete_group(this);
    for (std::vector<Group_Content*>::iterator it = people_.begin(); it != people_.end(); it ++)
        if ((*it)->person == deleting)
        {
            it = people_.erase(it);
            break;
        }
}

