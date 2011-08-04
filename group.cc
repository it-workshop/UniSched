#include <group.h>

Group::Group(std::string name)
{
    this->name = name;
}

Group::~Group(void)
{
}

std::string Group::get_Name(void)
{
    return name;
}

void Group::add_Human(Human *newbie)
{
    newbie->add_Group(this);
    humans.push_back(newbie);
}

