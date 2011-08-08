#include <usersinterface.h>

UsersInterface::UsersInterface(void)
{
    def_format = ASCII;
}

UsersInterface::~UsersInterface(void)
{
}

void UsersInterface::set_format(enum default_format new_format)
{
    def_format = new_format;
}

enum default_format UsersInterface::get_format(void)
{
    return def_format;
}

void UsersInterface::format(time_t *input)
{
    switch (def_format)
    {
    case ASCII:
        format_ASCII(input);
        break;
    default:
        break;
        //return format_RUS(input);
    }
}

void UsersInterface::format_ASCII(time_t *input)
{
    static const char days[7][4] = {
        "Sun",
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat"
    };
    static const char month[12][4] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };

    struct tm cutted = *localtime(input);

    std::cout<<days[cutted.tm_wday]<<' '<< month[cutted.tm_mon]<<' '<<cutted.tm_mday<<' '<<cutted.tm_hour<<':'<<cutted.tm_min<<' '<<(cutted.tm_year + 1900);
}

void UsersInterface::out_Person(Person *printing)
{
    std::cout<<printing->get_Name()<<' '<<printing->get_Surname()<<std::endl;
    for (std::vector<Group *>::iterator it = printing->get_Groups()->begin(); it != printing->get_Groups()->end(); it ++)
        std::cout<<(*it)->get_Name()<<' ';
    if (!printing->get_Groups()->empty())
        std::cout<<std::endl;
    out_Calendar(printing->get_Calendar());
}

void UsersInterface::out_Group(Group *printing)
{
    std::cout<<printing->get_Name()<<std::endl;
    for (std::vector<Person *>::iterator it = printing->get_People()->begin(); it != printing->get_People()->end(); it ++)
        std::cout<<(*it)->get_Name()<<' '<<(*it)->get_Surname()<<"  ";
    std::cout<<std::endl<<std::endl;
}

void UsersInterface::out_Event(Event *printing)
{
    std::cout<<"Begin: ";
    format(printing->get_Begin());
    std::cout<<" End: ";
    format(printing->get_End());
    std::cout<<std::endl;
    out_Group(printing->get_Group());
}

void UsersInterface::out_Calendar(Calendar *printing)
{
    if (printing->get_Events()->empty())
    {
        std::cout<<std::endl;
        return;
    }
    for (std::vector<Event *>::iterator it = printing->get_Events()->begin(); it != printing->get_Events()->end(); it ++)
    {
        std::cout<<"[(";
        format((*it)->get_Begin());
        std::cout<<")-(";
        format((*it)->get_End());
        std::cout<<") "<<(*it)->get_Name()<<"] ";
    }
    std::cout<<std::endl<<std::endl;
}

