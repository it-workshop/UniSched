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
        std::vector<StorableObject *> temp_cast_vector;
        for (auto it = groups_.begin(); it != groups_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

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
        std::vector<StorableObject *> temp_cast_vector = get_field_vector("groups");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            groups_.push_back(dynamic_cast<AbstractGroup *>(*it));
        }
    }
}

const std::string Person::read() const
{
    std::stringstream stream(std::stringstream::out);
    stream << "Name:\t " << name_ << std::endl
           << "Surname:\t " << surname_ << std::endl
           << "Sex:\n " << sex_ << std::endl
           << "Birhday:\t " << ctime(&birthday_) << std::endl
           << "Groups:\t " << ((groups_.empty()) ? "None" : "") << std::endl;

    for (auto it = groups_.begin(); it != groups_.end(); it++)
    {
        stream << "\t" << (*it)->read_string("name") << std::endl;
    }
}

const int Person::read_int(const std::string) const throw (std::bad_cast)
{
    throw std::bad_cast();
}

const std::string Person::read_string(const std::string name) const throw (std::bad_cast)
{
    if (name == "name")
        { return name_; }

    if (name == "surname")
        { return surname_; }

    throw std::bad_cast();
}

const time_t Person::read_time(const std::string name) const throw (std::bad_cast)
{
    if (name == "birthday")
        { return birthday_; }

    throw std::bad_cast();
}

const std::string Person::read_enum(const std::string name) const throw (std::bad_cast)
{
    if (name == "sex")
        { return _(sex_); }

    throw std::bad_cast();
}

const std::vector<UI::UsersObject *> Person::read_vector(const std::string name) const throw (std::bad_cast)
{
    if (name == "group")
    {
        std::vector<UI::UsersObject *> temp_cast_vector;
        for (auto it = groups_.begin(); it != groups_.end(); it++)
            { temp_cast_vector.push_back(*it); }

        return temp_cast_vector;
    }

    throw std::bad_cast();
}

void Person::update(const std::string name, const int value) throw (std::bad_cast)
{
    throw std::bad_cast();
}


void Person::update(const std::string name, const std::string value) throw (std::bad_cast)
{
    if (name == "name")
    {
        name_ = value;
        return;
    }

    if (name == "surname")
    {
        surname_ = value;
        return;
    }

    throw std::bad_cast();
}

void Person::update(const std::string name, const time_t value) throw (std::bad_cast)
{
    if (name == "time")
    {
        birthday_ = value;
        return;
    }

    throw std::bad_cast();
}

void Person::update_enum(const std::string name, const std::string value) throw (std::bad_cast)
{
    if (name == "sex")
    {
        sex_ == _(value);
        return;
    }

    throw std::bad_cast();
}

void Person::update(UI::UsersObject * object, bool linked) throw (std::bad_cast)
{
    (dynamic_cast<AbstractGroup *>(object))->update(this, linked);
}

