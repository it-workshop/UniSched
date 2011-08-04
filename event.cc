#include <event.h>

Event::Event(std::string name, time_t begin, time_t end)
{
    people = new Group (name); 
    this->name = name;
    this->begin = begin;
    this->end = end;
}

Event::~Event(void)
{
}

std::string Event::get_Name(void)
{
    return name;
}

time_t Event::get_Begin(void)
{
    return begin;
}

time_t Event::get_End(void)
{
    return end;
}

void Event::add_Human(Human *newbie)
{
    people->add_Human(newbie);
}

void Event::set_Time(time_t begin, time_t end)
{
    this->begin = begin;
    this->end = end;
}

