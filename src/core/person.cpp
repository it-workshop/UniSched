#include <person.h>

using namespace Core;

void Person::del_group (AbstractGroup const * group)
{
    for (auto it = groups_.begin(); it != groups_.end(); it++)
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
    set_field_enum("sex", _(sex_));
    set_field("birthday", birthday_);

    {
        std::vector<StorableObject const *> temp_cast_vector;
        for (auto it = groups_.begin(); it != groups_.end(); it++)
            temp_cast_vector.push_back(*it);

        set_field_vector("groups", temp_cast_vector);
    }
}

void Person::load()
{
    name_ = get_field_string("name");
    surname_ = get_field_string("surname");
    sex_ = _(get_field_string("sex"));
    birthday_ = get_field_time("birthday");

    groups_.clear();
    {
        std::vector<StorableObject const *> temp_cast_vector = get_field_vector("groups");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
            groups_.push_back(dynamic_cast<AbstractGroup const *>(*it));
    }
}
