#include <group.h>

using namespace Core;

const std::string Group::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (GROUP == object->type() || EVENT == object->type())
    {
        return "parent_groups";
    }
    return AbstractGroup::back_link_field(object);
}

