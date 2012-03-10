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
        if (typeid(std::vector<Object*>) != value.type()
        && typeid(std::pair<Object *,bool>) != value.type())
        {
            throw boost::bad_any_cast();
        }
        return;
    }
}

