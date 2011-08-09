#include <person.h>

Person::Person(std::string ID, std::string name, std::string surname, bool female, time_t birthday)
: ID_ (ID),
  name_ (name),
  surname_ (surname),
  female_ (female),
  birthday_ (birthday)
{
    events_ = new Calendar('c' + ID, "");
}

Person::~Person()
{
    delete events_;
}

std::string Person::get_ID()
{
    return ID_;
}

std::string Person::get_Name()
{
    return name_;
}

std::string Person::get_Surname()
{
    return surname_;
}

std::vector<Group*> *Person::get_Groups()
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

bool Person::is_female(void)
{
    return female_;
}

time_t *Person::birthday(void)
{
    return &birthday_;
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

