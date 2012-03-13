#include <person.h>

using namespace Core;

Person::Person(const objid_t id, AbstractUI& ui) throw (std::bad_cast):
    Object(PERSON, id, ui)
{
}

void Person::check_field(const std::string& name, const boost::any& value) const
        throw(boost::bad_any_cast)
{
    if ("name" == name)
    {
        boost::any_cast<std::string>(value);
        return;
    }
    if ("surname" == name)
    {
        boost::any_cast<std::string>(value);
        return;
    }
    if ("birtday" == name)
    {
        boost::any_cast<time_t>(value);
        return;
    }
    if ("sex" == name)
    {
        auto tmp = boost::any_cast<std::string>(value);
        if ("MALE" != tmp && "FEMALE" != tmp)
        {
            throw boost::bad_any_cast();
        }
        return;
    }
    if ("groups" == name)
    {
        throw boost::bad_any_cast();
    }
}

const std::string Person::link_field(const Object *object) const
        throw (std::bad_cast)
{
    dynamic_cast<const AbstractGroup *>(object);
    return "groups";
}

const std::string Person::back_link_field(const Object *object) const
        throw (std::bad_cast)
{
    return link_field(object);
}

