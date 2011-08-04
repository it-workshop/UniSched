#include <active_time.h>


Active_Time::Active_Time(unsigned short int arrival, unsigned short int dispetch)
{
    this->arrival = arrival;
    this->dispetch = dispetch;
}

Active_Time::~Active_Time(void)
{
}

unsigned short int Active_Time::get_Begin(void)
{
    return arrival;
}

unsigned short int Active_Time::get_End(void)
{
    return dispetch;
}

