#include <group.h>

Group::Group(std::string name)
{
    name_ = name;
}

Group::~Group(void)
{
}

std::string Group::get_Name(void)
{
    return name_;
}

std::vector<Person*> *Group::get_People(void)
{
    return &people_;
}

void Group::add_Person(Person *adding)
{
    adding->add_Group(this);
    people_.push_back(adding);
}

void Group::delete_Person(Person *deleting)
{
    deleting->delete_Group(this);
    for (std::vector<Person*>::iterator it = people_.begin(); it != people_.end(); it ++)
        if (*it == deleting)
        {
            it = people_.erase(it);
            break;
        }
}

