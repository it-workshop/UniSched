#include "userinterface.h"

UserInterface::UserInterface()
{
    done = false;
    def_format = ASCII;
}

UserInterface::~UserInterface()
{
}

void UserInterface::set_db (storage::DataStorage *db)
{
    db_ = db;
}

storage::DataStorage *UserInterface::get_db ()
{
    return db_;
}

void UserInterface::listen()
{
    while (!done)
    {
        cout << endl << "raspisator-? ";
        uiconsole::execute(get_request());
    }
}

vector<string> UserInterface::get_request()
{
    vector<string> request;
    char now;
    while (now != '\n')
    {
        string reading = "";
        now = getchar();
        while ((now != ' ') && (now != '\n'))
        {
            if (now == EOF)
            {
                request.push_back("exit");
                return request;
            }
            reading += now;
            now = getchar();
        }
        request.push_back(reading);
    }
    return request;
}

void UserInterface::exit()
{
    done = true;
}

void UserInterface::set_format(enum default_format new_format)
{
    def_format = new_format;
}

enum default_format UserInterface::get_format()
{
    return def_format;
}

void UserInterface::format(time_t input)
{
    switch (def_format)
    {
    case ASCII:
        format_ASCII(input);
        break;
    case DATE:
        format_DATE(input);
    default:
        break;
    }
}

void UserInterface::format_ASCII(time_t input)
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

    struct tm cutted = *localtime(&input);

    cout << days[cutted.tm_wday]
         << ' ' << month[cutted.tm_mon]
         << ' ' << cutted.tm_mday
         << ' ' << cutted.tm_hour
         << ':' << cutted.tm_min
         << ' ' << (cutted.tm_year + 1900);
}

void UserInterface::format_DATE(time_t input)
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

    struct tm cutted = *localtime(&input);

    cout << days[cutted.tm_wday]
         << ' ' << month[cutted.tm_mon]
         << ' ' << cutted.tm_mday
         << ' ' << (cutted.tm_year + 1900);
}

time_t UserInterface::get_time(string time)
{
    if (time.size() != 16)
        return 0;
    struct tm formated;
    formated.tm_sec = 1;
    formated.tm_min = atoi(time.c_str() + 3);
    formated.tm_hour = atoi(time.c_str());
    formated.tm_isdst = 0;
    formated.tm_mday = atoi(time.c_str() + 6);
    formated.tm_mon = atoi(time.c_str() + 9);
    formated.tm_year = atoi(time.c_str() + 12) - 1900;
    return mktime(&formated);
}

time_t UserInterface::get_birthday(string time)
{
    if (time.size() != 10)
        return 0;
    struct tm formated;
    formated.tm_sec = 1;
    formated.tm_min = 0;
    formated.tm_hour = 0;
    formated.tm_isdst = 0;
    formated.tm_mday = atoi(time.c_str());
    formated.tm_mon = atoi(time.c_str() + 3);
    formated.tm_year = atoi(time.c_str() + 6) - 1900;
    return mktime(&formated);
}

void UserInterface::print_person(Person *printing)
{
    if (printing->sex() == Person::FEMALE)
       cout << "Woman: ";
    else
       cout << "Man: ";
    cout << printing->get_name()
         << ' ' << printing->get_surname()
         << " ($"<<printing->get_id()
         << ')' << endl
         << "Birthday: ";
    format_DATE(printing->birthday());
    cout << endl
         << "Groups: "
         << endl;
    for (vector<Group_Content *>::iterator it = printing->get_groups()->begin(); it != printing->get_groups()->end(); it ++)
    {
        if (!(*it)->group->get_name().empty())
            cout << "    "
                 << (*it)->group->get_name() 
                 << ": " << (*it)->status
                 << endl;
    }
    cout << "Events:" << endl;
    print_calendar(printing->get_calendar());
    cout << endl;
}

void UserInterface::print_group(Group *printing)
{
    if (!printing->get_name().empty())
    {
        cout << "Group: "
             << printing->get_name()
             << " (@" << printing->get_id()
             << ")" << endl
             << printing->get_description() << endl
             << "Memebers: " << endl;
    }
    for (vector<Group_Content*>::iterator it = printing->get_people()->begin(); it != printing->get_people()->end(); it ++)
        cout << "    " << (*it)->person->get_name()
             << ' ' << (*it)->person->get_surname()
             << ": " << (*it)->status << endl;
    if (!printing ->get_name().empty())
    {
        cout << "Events: " << endl;
        print_calendar(printing->get_calendar());
    }
    cout << endl;
}

void UserInterface::print_event(Event *printing)
{
    cout << "Event: " << printing->get_name()
         << " (#" << printing->get_id() << ')'
         << endl << printing->get_description()
         << endl << "Begin: ";
    format(printing->get_begin());
    cout << endl << "End:   ";
    format(printing->get_end());
    cout << endl;
    print_group(printing->get_group());
}

void UserInterface::print_calendar(Calendar *printing)
{
    for (vector<Event *>::iterator it = printing->get_events()->begin(); it != printing->get_events()->end(); it ++)
    {
        cout << "    " << (*it)->get_name() << " (";
        format((*it)->get_begin());
        cout << ")-(";
        format((*it)->get_end());
        cout << ")" << endl;
    }
    cout << endl;
}

