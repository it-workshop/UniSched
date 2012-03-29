#include <person.h>

using namespace Core;

Person::Person(const objid_t id, AbstractUI& ui) throw (std::bad_cast):
    Object(PERSON, id, ui)
{
}

void Person::check_field(const std::wstring& name, const boost::any& value) const
        throw(boost::bad_any_cast)
{
    if (L"name" == name)
    {
        boost::any_cast<std::wstring>(value);
        return;
    }
    if (L"surname" == name)
    {
        boost::any_cast<std::wstring>(value);
        return;
    }
    if (L"birtday" == name)
    {
        boost::any_cast<time_t>(value);
        return;
    }
    if (L"sex" == name)
    {
        auto tmp = boost::any_cast<std::wstring>(value);
        if (L"MALE" != tmp && L"FEMALE" != tmp)
        {
            throw boost::bad_any_cast();
        }
        return;
    }
    if (L"groups" == name)
    {
        throw boost::bad_any_cast();
    }
}

const std::wstring Person::link_field(const Object *object) const
        throw (std::bad_cast)
{
    if (GROUP == object->type() || EVENT == object->type())
    {
        return L"groups";
    }
    throw std::bad_cast();
}

const std::wstring Person::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    return link_field(object);
}

const bool Person::disconnect_way(const std::wstring& name) const
        throw (std::bad_cast)
{
    if (L"groups" == name)
    {
        return true;
    }
    throw std::bad_cast();
}

