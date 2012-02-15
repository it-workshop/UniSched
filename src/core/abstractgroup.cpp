#include <abstractgroup.h>
#include <sstream>

using namespace Core;

AbstractGroup::AbstractGroup(const int id, Manager& manager)
        throw (std::bad_cast):
    ManageableObject(id, manager), name_("name"),
    child_groups_("child_groups"), people_("people")
    {
        name_ = dynamic_cast<const FieldString&>(pull("name"));
        child_groups_ = dynamic_cast<const FieldVector&>(pull("child_groups"));
        people_ = dynamic_cast<const FieldString&>(pull("people"));
    }

void AbstractGroup::add_child(AbstractGroup * group)
{
    child_groups_.add(group);
    push(FieldLink("child_groups", std::make_pair(group, true)));
}

void AbstractGroup::del_child(AbstractGroup * group)
{
    child_groups_.del(group);
    push(FieldLink("child_groups", std::make_pair(group, false)));
}

const Field& AbstractGroup::read(const std::string& name) throw (std::bad_cast)
{
    if (name == "name")
    {
        return name_;
    }
    if (name == "child_groups")
    {
        return child_groups_;
    }
    if (name == "people")
    {
        return people_;
    }
    throw std::bad_cast();
}

void AbstractGroup::update(const Field& field) throw (std::bad_cast)
{
    if (field.name() == "name")
    {
        name_ = dynamic_cast<const FieldString&>(field);
        push(field);
        return;
    }
    if (field.name() == "people")
    {
        if (field.type() == Field::LINK)
        {
            auto tmp = dynamic_cast<const FieldLink&>(field);
            if (tmp.value().second)
            {
                dynamic_cast<Person *>(tmp.value().first)->add_group(this);
            }
            else
            {
                dynamic_cast<Person *>(tmp.value().first)->del_group(this);
            }
            people_.commit(tmp);
            push(field);
            return;
        }
        people_ = dynamic_cast<const FieldVector&>(field);
        return;
    }
    if (field.name() == "child_groups")
    {
        child_groups_ = dynamic_cast<const FieldVector&>(field);
        push(field);
        return;
    }
    throw std::bad_cast();
}

