#include <userinterface.h>

UserInterface::UserInterface(void)
{
    def_format = ASCII;
}

UserInterface::~UserInterface(void)
{
}

void UserInterface::set_format(enum default_format new_format)
{
    def_format = new_format;
}

enum default_format UserInterface::get_format(void)
{
    return def_format;
}

void UserInterface::format(time_t *input)
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

void UserInterface::format_ASCII(time_t *input)
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

    std::cout << days[cutted.tm_wday]
              << ' ' << month[cutted.tm_mon]
              << ' ' << cutted.tm_mday
              << ' ' << cutted.tm_hour
              << ':' << cutted.tm_min
              << ' ' << (cutted.tm_year + 1900);
}

void UserInterface::print_person(Person *printing)
{
    if (printing->is_female())
       cout << "Woman: ";
    else
       cout << "Man: ";
    cout << printing->get_name()
         << ' ' << printing->get_surname()
         << " ("<<printing->get_id()
         << ')' << endl
         << "Birthday: ";
    format(printing->birthday());
    cout << endl
         << "Groups: "
         << endl;
    for (vector<Group_Content *>::iterator it = printing->get_groups()->begin(); it != printing->get_groups()->end(); it ++)
    {
        if ((*it)->group->get_name().empty())
            cout << "    "
                 << (*it)->group->get_name() 
                 << ": " << (*it)->status
                 << endl;
    }
    cout << "Events:" << endl;
    print_calendar(printing->get_calendar());
    for (vector<Group_Content *>::iterator it = printing->get_groups()->begin(); it != printing->get_groups()->end(); it ++)
        print_calendar((*it)->group->get_calendar());
    cout << endl;
}

void UserInterface::print_group(Group *printing)
{
    if (printing->get_name().empty())
    {
        std::cout << "Group: "
                  << printing->get_name()
                  << " (" << printing->get_id()
                  << ")" << std::endl
                  << printing->get_description() << std::endl << "Memebers: " << std::endl;
    }
    for (std::vector<Group_Content*>::iterator it = printing->get_people()->begin(); it != printing->get_people()->end(); it ++)
        std::cout << "    " << (*it)->person->get_name() << ' ' << (*it)->person->get_surname() << ": " << (*it)->status << std::endl;
    if (printing ->get_name() != "")
    {
        std::cout << "Events: " << std::endl;
        print_calendar(printing->get_calendar());
    }
    std::cout << std::endl;
}

void UserInterface::print_event(Event *printing)
{
    std::cout << "Event: " << printing->get_name() << " (" << printing->get_id() << ')' << std::endl << printing->get_description() << std::endl << "Begin: ";
    format(printing->get_begin());
    std::cout << std::endl << "End:   ";
    format(printing->get_end());
    std::cout << std::endl;
    print_group(printing->get_group());
}

void UserInterface::print_calendar(Calendar *printing)
{
    if (printing->get_name() != "")
        std::cout << "Calendar: " << printing->get_name() << std::endl;
    for (std::vector<Event *>::iterator it = printing->get_events()->begin(); it != printing->get_events()->end(); it ++)
    {
        std::cout << "    [" << (*it)->get_name() << " (";
        format((*it)->get_begin());
        std::cout << ")-(";
        format((*it)->get_end());
        std::cout << ")]" << std::endl;
    }
}

