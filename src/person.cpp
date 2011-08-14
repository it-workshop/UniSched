#include <person.h>

Person::Person(id_type id, std::string name, std::string surname, enum Person::Sex sex, time_t birthday)
: id_ (id),
  name_ (name),
  surname_ (surname),
  sex_ (sex),
  birthday_ (birthday)
{
}

Person::~Person()
{
    for (std::vector<Group_Content *>::iterator it = groups_.begin(); it != groups_.end(); it ++)
        (*it)->group->delete_person(this);
}

id_type Person::get_id()
{
    return id_;
}

std::string Person::get_name()
{
    return name_;
}

std::string Person::get_surname()
{
    return surname_;
}

std::vector<Group_Content*> *Person::get_groups()
{
    return &groups_;
}

void Person::add_group(struct Group_Content_ *adding)
{
    groups_.push_back(adding);
}

void Person::delete_group(Group *deleting)
{
    for (std::vector<Group_Content*>::iterator it = groups_.begin(); it != groups_.end(); it ++)
        if ((*it)->group == deleting)
	{
            it = groups_.erase(it);
            break;
        }
}

enum Person::Sex Person::sex()
{
    return sex_;
}

time_t Person::birthday()
{
    return birthday_;
}

Calendar *Person::get_calendar()
{
    Calendar *all = new Calendar(0);
    for (std::vector<Group_Content *>::iterator it = groups_.begin(); it != groups_.end(); it ++)
        if (!(*it)->group->get_name().empty())
            all->merge_calendar((*it)->group->get_calendar());
    return all;
}

void Person::add_event(Event *adding, std::string status)
{
    adding->add_person(this, status);
}

void Person::delete_event(Event *deleting)
{
    deleting->delete_person(this);
}

