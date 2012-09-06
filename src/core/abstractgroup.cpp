#include <abstractgroup.h>

using namespace Core;

AbstractGroup::AbstractGroup(obj_t type, objid_t id, AbstractUI& ui):
    Object(type, id, ui)
{
}

void AbstractGroup::check_field(const std::string& name,
        const boost::any& value) const throw (boost::bad_any_cast)
{
    if ("name" == name)
    {
        boost::any_cast<std::string>(value);
        return;
    }
    if ("people" == name || "children_groups" == name)
    {
        throw boost::bad_any_cast();
    }
}

const std::string AbstractGroup::link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (object->type() == PERSON)
    {
        return "people";
    }
    if (object->type() == GROUP)
    {
        return "children_groups";
    }
    throw std::bad_cast();
}

const std::string AbstractGroup::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (PERSON == object->type())
    {
        return "people";
    }
    throw std::bad_cast();
}

const bool AbstractGroup::disconnect_way(const std::string& name) const
        throw (std::bad_cast)
{
    if ("people" == name || "children_groups" == name)
    {
        return true;
    }
    throw std::bad_cast();
}

