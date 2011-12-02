#include <group.h>

using namespace Core;

void Group::add_parent_group(AbstractGroup *group)
{
    for (std::vector<AbstractGroup const *>::iterator it = parent_groups_.begin(); it != parent_groups_.end(); it++)
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
    for (std::vector<AbstractGroup const *>::iterator it = parent_groups_.begin(); it != parent_groups_.end(); it++)
    {
        if (*it == group)
        {
            parent_groups_.erase(it);
            break;
        }
    }
}
