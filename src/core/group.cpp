#include <group.h>

using namespace Core;

void Group::check_field(const std::string& name, const boost::any& value) const
    throw(boost::bad_any_cast, std::bad_cast)
{
    AbstractGroup::check_field(name, value);
    if ("parent_groups" == name)
    {
        if (typeid(std::vector<Object *>) != value.type())
        {
            dynamic_cast<AbstractGroup *>(
                boost::any_cast<std::pair<Object *, bool>>(value).first);
        }
        return;
    }
}

