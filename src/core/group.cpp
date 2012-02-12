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

    {
        auto temp_vector = get_field_vector("parent_groups");
        temp_vector.push_back(group);
        set_field_vector("parent_groups", temp_vector);
    }
}

void Group::del_parent_group(AbstractGroup *group)
{
    for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
    {
        if (*it == group)
        {
            parent_groups_.erase(it);
            group->del_child(this);
            break;
        }
    }

    auto temp_vector = get_field_vector("parent_groups");
    for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
    {
        if (*it == group)
        {
            temp_vector.erase(it);
            break;
        }
    }
}

void Group::save()
{
    AbstractGroup::save();

    {
        std::vector<ManagersObject *> temp_cast_vector;
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
            parent_groups_.push_back(dynamic_cast<AbstractGroup *>(*it));
        }
    }
}

const std::string Group::read() const
{
    std::stringstream stream (std::stringstream::out);
    stream << AbstractGroup::read()
           << "Parent groups:\t "
           << (parent_groups_.empty() ? "None" : "") << std::endl;

    for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
        { stream << "\t" << (*it)->read_string("name") << std::endl; }
}

const std::vector<UI::UsersObject *> Group::read_vector(const std::string name) const throw (std::bad_cast)
{
    if (name == "parent_groups")
    {
        std::vector<UI::UsersObject *> temp_cast_vector;
        for (auto it = parent_groups_.begin(); it != parent_groups_.end(); it++)
            { temp_cast_vector.push_back(*it); }
        
        return temp_cast_vector;
    }

    return AbstractGroup::read_vector(name);
}

void Group::update(UI::UsersObject * object, const bool linked) throw (std::bad_cast)
{
    try
    {
        AbstractGroup::update(object, linked);
    }
    catch (std::bad_cast)
    {
        if (linked)
            { add_parent_group(dynamic_cast<AbstractGroup *>(object)); }
        else
            { del_parent_group(dynamic_cast<AbstractGroup *>(object)); }
    }
}

