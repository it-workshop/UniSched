#include <person.h>

using namespace Core;

void Person::del_group (AbstractGroup const * group)
{
    for (std::vector<AbstractGroup const *>::iterator it = groups_.begin(); it != groups_.end(); it++)
    {
        if (*it == group)
        {
            groups_.erase(it);
            break;
        }
    }
}

void Person::save()
{
    set_field("name", name_);
    set_field("surname", surname_);
    set_field("sex", (sex_ == MALE)?"MALE":"FEMALE");
    set_field("birthday", birthday_);

    /* TODO: need something to save groups_ field, need interface. */
}

void Person::load()
{
    name_ = get_field_string("name");
    surname_ = get_field_string("surname");
    sex_ = (std::string("MALE") == get_field_string("sex"))?MALE:FEMALE;
    birthday_ = get_field_time("birthday");

    /* TODO: need something to load groups_ field, need interface. */
}
