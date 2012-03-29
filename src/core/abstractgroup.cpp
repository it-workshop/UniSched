#include <abstractgroup.h>

using namespace Core;

AbstractGroup::AbstractGroup(obj_t type, objid_t id, AbstractUI& ui):
    Object(type, id, ui)
{
}

void AbstractGroup::check_field(const std::wstring& name,
        const boost::any& value) const throw (boost::bad_any_cast, std::bad_cast)
{
    if (L"name" == name)
    {
        boost::any_cast<std::wstring>(value);
        return;
    }
    if (L"people" == name || L"children_groups")
    {
        throw boost::bad_any_cast();
    }
}

const std::wstring AbstractGroup::link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (object->type() == PERSON)
    {
        return L"people";
    }
    if (object->type() == GROUP)
    {
        return L"children_groups";
    }
    throw std::bad_cast();
}

const std::wstring AbstractGroup::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (PERSON == object->type())
    {
        return L"people";
    }
    throw std::bad_cast();
}

const bool AbstractGroup::disconnect_way(const std::wstring& name) const
        throw (std::bad_cast)
{
    if (L"people" == name || L"children_groups" == name)
    {
        return true;
    }
    throw std::bad_cast();
}

