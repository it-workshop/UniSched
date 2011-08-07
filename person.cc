#include <person.h>

Person::Person(std::string name, std::string surname)
{
    name_ = name;
    surname_ = surname;

    events_ = new Calendar ();
}

Person::~Person(void)
{
    delete events_;
}

std::string Person::get_Name(void)
{
    return name_;
}

std::string Person::get_Surname(void)
{
    return surname_;
}

std::vector<Group*> *Person::get_Groups(void)
{
    return &groups_;
}

void Person::add_Group(Group *adding)
{
    groups_.push_back(adding);
}

void Person::delete_Group(Group *deleting)
{
    for (std::vector<Group*>::iterator it = groups_.begin(); it != groups_.end(); it ++)
        if (*it == deleting)
	{
            it = groups_.erase(it);
            break;
        }
}

Calendar *Person::get_Calendar(void)
{
    return events_;
}

void Person::add_Event(Event *adding)
{
    events_->add_Event(adding);
    adding->add_Person(this);
}

void Person::delete_Event(Event *deleting)
{
    events_->delete_Event(deleting);
    deleting->delete_Person(this);
}

