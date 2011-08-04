#include <human.h>

Human::Human(std::string name, std::string surname, Active_Time active)
{
    this->name = name;
    this->surname = surname;
    this->active.push_back(active);
}

Human::~Human(void)
{
}

std::string Human::get_Name(void)
{
    return name;
}

std::string Human::get_SurName(void)
{
    return surname;
}

void Human::add_Group(Group *newbie)
{
    groups.push_back(newbie);
}

void Human::add_Active(Active_Time active)
{
    this->active.push_back(active);
}

bool Human::is_Active(unsigned short int date)
{
    for (std::vector<Active_Time>::iterator it = active.begin(); it != active.end(); it++)
    {
        if ((*it).get_Begin() <= date && (*it).get_End() >= date)
	    return true;
    }

    return false;
}

