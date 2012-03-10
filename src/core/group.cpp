#include <group.h>

using namespace Core;

const std::string Group::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    try
    {
        dynamic_cast<const AbstractGroup *>(object);
        return "parent_groups";
    }
    catch (std::bad_cast)
    {}
    return AbstractGroup::back_link_field(object);
}

