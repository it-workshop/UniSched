#include <group.h>

using namespace Core;

void Group::add_parent_group(AbstractGroup *group)
{
    for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
    {
        if (*it == group)
        {
            return;
        }
    }

    parent_groups_.push_back(group);
    group->add_child(this);
}

void Group::del_parent_group(AbstractGroup *group)
{
    for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
    {
        if (*it == group)
        {
            parent_groups_.erase(it);
            break;
        }
    }
}

void Group::save()
{
    AbstractGroup::save();

    {
        std::vector<StorableObject const *> temp_cast_vector;
        for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

        set_field_vector("parent_groups", temp_cast_vector);
    }
}

void Group::load()
{
    AbstractGroup::load();

    {
        parent_groups_.clear();

        auto temp_cast_vector = get_field_vector("parent_groups");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            parent_groups_.push_back(dynamic_cast<AbstractGroup const *>(*it));
        }
    }
}

