#include <group.h>

using namespace Core;

void Group::check_field(const std::wstring& name, const boost::any& value) const
        throw (boost::bad_any_cast)
{
    AbstractGroup::check_field(name, value);
    if (L"parent_groups" == name)
    {
        throw boost::bad_any_cast();
    }
}

const std::wstring Group::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (GROUP == object->type() || EVENT == object->type())
    {
        return L"parent_groups";
    }
    return AbstractGroup::back_link_field(object);
}

const bool Group::disconnect_way(const std::wstring& name) const
        throw (std::bad_cast)
{
    if (L"parent_groups" == name)
    {
        return false;
    }
    return AbstractGroup::disconnect_way(name);
}

