#include <group.h>

using namespace Core;

const Field& Group::read(const std::string& name) const throw (std::bad_cast)
{
    if (name == "parent_groups")
    {
        return parent_groups_;
    }
    return AbstractGroup::read(name);
}

void Group::update(const Field& field) throw (std::bad_cast)
{
    if (field.name() == "parent_groups")
    {
        if (field.type() == Field::LINK)
        {
            auto tmp = dynamic_cast<const FieldLink&>(field);
            (dynamic_cast<AbstractGroup *>(tmp.value().first))->add_child(this);
            parent_groups_.commit(tmp);
            push(tmp);
            return;
        }
        parent_groups_ = dynamic_cast<const FieldVector&>(field);
        return;
    }
    AbstractGroup::update(field);
}

