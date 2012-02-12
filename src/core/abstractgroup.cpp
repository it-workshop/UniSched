#include <abstractgroup.h>
#include <sstream>

using namespace Core;

void AbstractGroup::add_child(AbstractGroup * group)
{
    child_groups_.push_back(group);
    auto temp_vector = get_field_vector("child_groups");
    temp_vector.push_back(group);
    set_field_vector("child_groups", temp_vector);
}

void AbstractGroup::del_child(AbstractGroup * group)
{
    for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
    {
        if (*it == group)
        {
            child_groups_.erase(it);
            break;
        }
    }

    auto temp_vector = get_field_vector("child_groups");
    for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
    {
        if (*it == group)
        {
            temp_vector.erase(it);
            break;
        }
    }
    set_field_vector("child_groups", temp_vector);
}

void AbstractGroup::add_person(Person * person)
{
    for (auto it = people_.begin(); it != people_.end(); it++)
    {
        if (*it == person)
        {
            return;
        }
    }

    people_.push_back(person);
    person->add_group(this);

    auto temp_vector = get_field_vector("people");
    temp_vector.push_back(person);
    set_field_vector("person", temp_vector);
}

void AbstractGroup::del_person(Person * person)
{
    for (auto it = people_.begin(); it != people_.end(); it++)
    {
        if (*it == person)
        {
            people_.erase(it);
            break;
        }
    }

    auto temp_vector = get_field_vector("people");
    for (auto it = temp_vector.begin(); it != temp_vector.end(); it++)
    {
        if (*it == person)
        {
            temp_vector.erase(it);
            break;
        }
    }
    set_field_vector("person", temp_vector);
}

void AbstractGroup::save()
{
    set_field("name", name_);

    {
        std::vector<ManagersObject *> temp_cast_vector;
        for (auto it = people_.begin(); it != people_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

        set_field_vector("people", temp_cast_vector);
    }

    {
        std::vector<ManagersObject *> temp_cast_vector;
        for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
        {
            temp_cast_vector.push_back(*it);
        }

        set_field_vector("child_groups", temp_cast_vector);
    }
}

void AbstractGroup::load()
{
    name_ = get_field_string("name");

    {
        people_.clear();

        auto temp_cast_vector = get_field_vector("people");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            people_.push_back(dynamic_cast<Person *>(*it));
        }

        set_field_vector("people", temp_cast_vector);
    }

    {
        child_groups_.clear();

        auto temp_cast_vector = get_field_vector("child_groups");
        for (auto it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            child_groups_.push_back(dynamic_cast<AbstractGroup *>(*it));
        }
    }
}

const std::string AbstractGroup::read() const
{
    std::stringstream stream(std::stringstream::out);

    stream << "Name:\t\t " << name_ << std::endl
           << "People:\t\t " << ((people_.empty()) ? "None" : "") << std::endl;

    for (auto it = people_.begin(); it != people_.end(); it++)
    {
        stream << "\t" << (*it)->read_string("name")
               << " " << (*it)->read_string("surname") << std::endl;
    }

    stream << "Child groups:\t " << ((child_groups_.empty()) ? "None" : "") << std::endl;

    for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
    {
        stream << "\t" << (*it)->read_string("name") << std::endl;
    }

    return stream.str();
}

const int AbstractGroup::read_int(const std::string name) const throw (std::bad_cast)
{
    throw std::bad_cast();
}

const std::string AbstractGroup::read_string(const std::string name) const throw (std::bad_cast)
{
    if (name == "name")
    { return name_; }

    throw std::bad_cast();
}

const time_t AbstractGroup::read_time(const std::string name) const throw (std::bad_cast)
{
    throw std::bad_cast();
}

const std::string AbstractGroup::read_enum(const std::string name) const throw (std::bad_cast)
{
    throw std::bad_cast();
}

const std::vector<UI::UsersObject *> AbstractGroup::read_vector(const std::string name) const throw (std::bad_cast)
{
    if (name == "people")
    {
        std::vector<UI::UsersObject *> temp_cast_vector;
        for (auto it = people_.begin(); it != people_.end(); it++)
            { temp_cast_vector.push_back(*it); }

        return temp_cast_vector;
    }

    if (name == "child_groups")
    {
        std::vector<UI::UsersObject *> temp_cast_vector;
        for (auto it = child_groups_.begin(); it != child_groups_.end(); it++)
            { temp_cast_vector.push_back(*it); }

        return temp_cast_vector;
    }

    throw std::bad_cast();
}

void AbstractGroup::update(const std::string name, const int value) throw (std::bad_cast)
{
    throw std::bad_cast();
}

void AbstractGroup::update(const std::string name, const std::string value) throw (std::bad_cast)
{
    if (name == "name")
    {
        name_ = value;
        set_field("name", name_);
        return;
    }

    throw std::bad_cast();
}

void AbstractGroup::update(const std::string name, const time_t value) throw (std::bad_cast)
{
    throw std::bad_cast();
}

void AbstractGroup::update_enum(const std::string name, const std::string value) throw (std::bad_cast)
{
    throw std::bad_cast();
}

void AbstractGroup::update(UI::UsersObject * object, const bool linked) throw (std::bad_cast)
{
    if (linked)
        { add_person(dynamic_cast<Person *>(object)); }
    else
        { del_person(dynamic_cast<Person *>(object)); }
}


