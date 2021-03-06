#include <group.h>

using namespace Core;

void Group::check_field(const std::string& name, const boost::any& value) const
        throw (boost::bad_any_cast)
{
    AbstractGroup::check_field(name, value);
    if ("parent_groups" == name)
    {
        throw boost::bad_any_cast();
    }
}

const std::string Group::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (GROUP == object->type() || EVENT == object->type())
    {
        return "parent_groups";
    }
    return AbstractGroup::back_link_field(object);
}

const bool Group::disconnect_way(const std::string& name) const
        throw (std::bad_cast)
{
    if ("parent_groups" == name)
    {
        return false;
    }
    return AbstractGroup::disconnect_way(name);
}

