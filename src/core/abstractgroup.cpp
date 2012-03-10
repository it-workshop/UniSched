#include <abstractgroup.h>
#include <sstream>

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
    if ("child_groups" == name)
    {
        if (typeid(std::vector<Object*>) != value.type())
        {
            dynamic_cast<AbstractGroup *>(
                boost::any_cast<std::pair<Object *,bool>>(value).first);
        }
        return;
    }
}

