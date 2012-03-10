#include <abstractgroup.h>
#include <group.h>

using namespace Core;

AbstractGroup::AbstractGroup(obj_t type, objid_t id, AbstractUI& ui):
    Object(type, id, ui)
{
}

void AbstractGroup::check_field(const std::string& name,
        const boost::any& value) const throw (boost::bad_any_cast, std::bad_cast)
{
    if ("name" == name)
    {
        boost::any_cast<std::string>(value);
        return;
    }
    if ("begin" == name || "duration" == name)
    {
        boost::any_cast<time_t>(value);
        return;
    }
}

const std::string AbstractGroup::link_field(const Object *object) const
        throw (std::bad_cast)
{
    try
    {
        dynamic_cast<const Person *>(object);
        return "people";
    }
    catch (std::bad_cast)
    {}

    dynamic_cast<const Group *>(object);
    return "children_groups";
}

const std::string AbstractGroup::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    dynamic_cast<const Person *>(object);
    return "people";
}

