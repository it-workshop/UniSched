#include <person.h>

Person::Person(std::string id, std::string name, std::string surname, bool female, time_t birthday)
: id_ (id),
  name_ (name),
  surname_ (surname),
  female_ (female),
  birthday_ (birthday)
{
    events_ = new Calendar('c' + id, "");
}

Person::~Person()
{
    delete events_;
}

std::string Person::get_id()
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

/*void Person::add_group(Group *adding, std::string status)
{
    Group_Content a;
    a.person = this;
    a.group = adding;
    a.status = status;
    groups_.push_back(&a);
}*/

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

bool Person::is_female(void)
{
    return female_;
}

time_t *Person::birthday(void)
{
    return &birthday_;
}

bool Person::in_event(Event *event)
{
    if (events_->has_event(event))
        return true;
    for (std::vector<Group_Content*>::iterator it = groups_.begin(); it != groups_.end(); it ++)
        if ((*it)->group->get_calendar()->has_event(event))
            return true;
    return false;
}

Calendar *Person::get_calendar(void)
{
    return events_;
}

void Person::add_event(Event *adding, std::string status)
{
    events_->add_event(adding);
    adding->add_person(this, status);
}

void Person::delete_event(Event *deleting)
{
    events_->delete_event(deleting);
    deleting->delete_person(this);
}

