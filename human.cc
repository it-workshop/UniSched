#include <human.h>

Human::Human(std::string name, std::string surname)
{
    this->name = name;
    this->surname = surname;
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

