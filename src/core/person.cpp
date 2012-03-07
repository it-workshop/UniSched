#include <person.h>

using namespace Core;

Person::Person(obj_t type, objid_t id, AbstractUI& ui) throw (std::bad_cast):
    Object(type, id, ui), name_("name"), surname_("surname"),
    sex_("sex", "MALE"), birthday_("birthday"), groups_("groups")
{
    name_ = dynamic_cast<const FieldString&>(pull("name"));
    surname_ = dynamic_cast<const FieldString&>(pull("surname"));
    {
        auto tmp= dynamic_cast<const FieldEnum&>(pull("sex"));
        if (tmp.value() == "MALE" || tmp.value() == "FEMALE")
        {
            sex_ = tmp;
        }
        throw std::bad_cast();
    }
    birthday_ = dynamic_cast<const FieldTime&>(pull("birthday"));
    groups_ = dynamic_cast<const FieldTime&>(pull("groups"));
}

const Field& Person::read(const std::string& name) const throw (std::bad_cast)
{
    if (name == "name")
    {
        return name_;
    }
    if (name == "surname")
    {
        return surname_;
    }
    if (name == "sex")
    {
        return sex_;
    }
    if (name == "birthday")
    {
        return birthday_;
    }
    if (name == "groups")
    {
        return groups_;
    }
    throw std::bad_cast();
}

void Person::update(const Field& field) throw (std::bad_cast)
{
    if (field.name() == "name")
    {
        name_ = dynamic_cast<const FieldString&>(field);
        return;
    }
    if (field.name() == "surname")
    {
        surname_ = dynamic_cast<const FieldString&>(field);
        return;
    }
    if (field.name() == "sex")
    {
        auto tmp = dynamic_cast<const FieldEnum&>(field);
        if (tmp.value() == "MALE" || tmp.value() == "FEMALE")
        {
            sex_ = tmp;
            return;
        }
        throw std::bad_cast();
    }
    if (field.name() == "birthday")
    {
        birthday_ = dynamic_cast<const FieldTime&>(field);
        return;
    }
    if (field.name() == "groups")
    {
        if (groups_.type() == Field::LINK)
        {
            groups_.commit(dynamic_cast<const FieldLink&>(field));
            return;
        }
        groups_ = dynamic_cast<const FieldVector&>(field);
    }
    throw std::bad_cast();
}

