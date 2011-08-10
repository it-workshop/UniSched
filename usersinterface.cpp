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

    std::cout << days[cutted.tm_wday] << ' ' << month[cutted.tm_mon] << ' ' << cutted.tm_mday << ' ' << cutted.tm_hour << ':' << cutted.tm_min << ' ' << (cutted.tm_year + 1900);
}

void UsersInterface::print_person(Person *printing)
{
    if (printing->is_female())
       std::cout << "Woman: ";
    else
       std::cout << "Man: ";
    std::cout << printing->get_name() << ' ' << printing->get_surname() << " ("<<printing->get_id() << ')' << std::endl << "Birthday: ";
    format(printing->birthday());
    std::cout << std::endl;
    for (std::vector<Group *>::iterator it = printing->get_groups()->begin(); it != printing->get_groups()->end(); it ++)
        if ((*it)->get_name() != "")
            std::cout << (*it)->get_name() << ' ';
    if (!printing->get_groups()->empty())
        std::cout << std::endl;
    print_calendar(printing->get_calendar());
    for (std::vector<Group *>::iterator it = printing->get_groups()->begin(); it != printing->get_groups()->end(); it ++)
        print_calendar((*it)->get_calendar());
    std::cout << std::endl << std::endl;
}

void UsersInterface::print_group(Group *printing)
{
    if (printing->get_name() != "")
        std::cout << printing->get_name() << " (" << printing->get_id() << ')' << std::endl << printing->get_description() << std::endl;
    for (std::vector<Person *>::iterator it = printing->get_people()->begin(); it != printing->get_people()->end(); it ++)
        std::cout << (*it)->get_name() << ' ' << (*it)->get_surname() << "  ";
    if (printing ->get_name() != "")
    {
        std::cout << std::endl << "Events: ";
        print_calendar(printing->get_calendar());
    }
    std::cout << std::endl << std::endl;
}

void UsersInterface::print_event(Event *printing)
{
    std::cout << printing->get_name() << " (" << printing->get_id() << ')' << std::endl << printing->get_description() << std::endl << "Begin: ";
    format(printing->get_begin());
    std::cout << " End: ";
    format(printing->get_end());
    std::cout << std::endl;
    print_group(printing->get_group());
}

void UsersInterface::print_calendar(Calendar *printing)
{
    if (printing->get_name() != "")
        std::cout << printing->get_name() << std::endl;
    if (printing->get_events()->empty())
    {
        std::cout << std::endl;
        return;
    }
    for (std::vector<Event *>::iterator it = printing->get_events()->begin(); it != printing->get_events()->end(); it ++)
    {
        std::cout << '[' << (*it)->get_name() << " (";
        format((*it)->get_begin());
        std::cout << ")-(";
        format((*it)->get_end());
        std::cout << ")]  ";
    }
}

