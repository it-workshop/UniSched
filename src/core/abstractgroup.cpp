#include <abstractgroup.h>

using namespace Core;

void AbstractGroup::del_child(AbstractGroup const * group)
{
    for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
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
    for (auto it = people_.begin(); it != people_.end(); it++)
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
    for (auto it = people_.begin(); it != people_.end(); it++)
    {
        if (*it == person)
        {
            people_.erase(it);
            break;
        }
    }
}

void AbstractGroup::save()
{
    set_field("name", name_);

    {
        std::vector<StorableObject const *> temp_cast_vector;
        for (auto it = people_.begin(); it != people_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

        set_field_vector("people", temp_cast_vector);
    }

    {
        std::vector<StorableObject const *> temp_cast_vector;
        for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

        set_field_vector("child_groups", temp_cast_vector);
    }
}

void AbstractGroup::load()
{
    name_ = get_field_string("name");

    {
        people_.clear();

        auto temp_cast_vector = get_field_vector("people");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            people_.push_back(dynamic_cast<Person const *>(*it));
        }

        set_field_vector("people", temp_cast_vector);
    }

    {
        child_groups_.clear();

        auto temp_cast_vector = get_field_vector("child_groups");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            child_groups_.push_back(dynamic_cast<AbstractGroup const *>(*it));
        }
    }
}
