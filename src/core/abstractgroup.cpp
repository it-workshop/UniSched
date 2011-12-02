#include <abstractgroup.h>

using namespace Core;

void AbstractGroup::del_child(AbstractGroup const * group)
{
    for (std::vector<AbstractGroup const *>::iterator it = child_groups_.begin(); it != child_groups_.end(); it++)
    {
        if (*it == group)
        {
            child_groups_.erase(it);
            break;
        }
    }
}

void AbstractGroup::add_person(Person * person)
{
    for (std::vector<Person const *>:: iterator it = people_.begin(); it != people_.end(); it++)
    {
        if (*it == person)
        {
            return;
        }
    }

    people_.push_back(person);
    person->add_group(this);
}

void AbstractGroup::del_person(Person * person)
{
    for (std::vector<Person const *>::iterator it = people_.begin(); it != people_.end(); it++)
    {
        if (*it == person)
        {
            people_.erase(it);
            break;
        }
    }
}

