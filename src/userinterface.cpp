#include <userinterface.h>

UserInterface::UserInterface(void)
{
    def_format = ASCII;
}

UserInterface::~UserInterface(void)
{
}

void UserInterface::listen(vector<Person *> *persons, vector<Group *> *groups, vector<Event *> *events, vector<Calendar *> *calendars)
{
    string reading;
    while (true)
    {
        id_t id, id1;
        char symbol;
        cout << "raspisator-? ";
        cin >> reading;
        if (reading == "merge")
        {
            cin >> symbol;
            switch (symbol)
            {
            case '@':
                cin >> id >> symbol >> id1;
                (*groups)[id / 2]->merge_group((*groups)[id1 / 2]);
                break;
            case '%':
                cin >> id >> symbol >> id1;
                (*calendars)[id / 3]->merge_calendar((*calendars)[id / 3]);
                break;
            default:
                cout << "Only group and calendar can be cloned";
            }
            continue;
        }
        if (reading == "exclude")
        {
            cin >> symbol >> id;
            if (symbol != '@')
                cout << "Only groups can be excluded";
            cin >> symbol >> id1;
            if (symbol != '@')
                cout << "Only groups can be excluded";
            (*groups)[id / 2]->exclude_group((*groups)[id1 / 2]);
            continue;
        }
        if (reading == "include")
        {
            cin >> symbol >> id;
            if (symbol != '@')
                cout << "Only groups can be included";
            cin >> symbol >> id1;
            if (symbol != '@')
                cout << "Only groups can be included";
            (*groups)[id / 2]->include_group((*groups)[id1 / 2]);
            continue;
        }
        if (reading == "clone")
        {
            cin >> symbol;
            switch (symbol)
            {
            case '@':
                cin >> id;
                groups->push_back(new Group(2 * groups->size(), (*groups)[id / 2]));
                break;
            case '%':
                cin >> id;
                calendars->push_back(new Calendar(3 * calendars->size(), (*calendars)[id / 3]));
                break;
            default:
                cout << "Only groups and calendars can be cloned" << endl;
            }
            continue;
        }
        if (reading == "print")
        {
            cin >> symbol;
            switch (symbol)
            {
            case '$':
                cin >> id;
                print_person((*persons)[id]);
                break;
            case '@':
                cin >> id;
                print_group((*groups)[id]);
                break;
            case '#':
                cin >> id;
                print_event((*events)[id]);
                break;
            case '%':
                cin >> id;
                print_calendar((*calendars)[id]);
                break;
            default:
                cout << "Only person, group, event and calendar can be printed" << endl;
            }
            continue;
        }
        if (reading == "all")
        {
            cin >> symbol;
            switch (symbol)
            {
            case '$':
                for (vector<Person *>::iterator it = persons->begin(); it != persons->end(); it ++)
                    print_person(*it);
                break;
            case '@':
                for (vector<Group *>::iterator it = groups->begin(); it != groups->end(); it ++)
                    print_group(*it);
                break;
            case '#':
                for (vector<Event *>::iterator it = events->begin(); it != events->end(); it ++)
                    print_event(*it);
                break;
            case '%':
                for (vector<Calendar *>::iterator it = calendars->begin(); it != calendars->end(); it ++)
                    print_calendar(*it);
                break;
            default:
                cout << "Only person, group, event and calendar can be printed" << endl;
            }
            continue;
        }
        if (reading == "exit")
            return;
        cout << "There's no function: " << reading << endl;
    }
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
    default:
        break;
        //return format_RUS(input);
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

void UserInterface::print_person(Person *printing)
{
    if (printing->is_female())
       cout << "Woman: ";
    else
       cout << "Man: ";
    cout << printing->get_name()
         << ' ' << printing->get_surname()
         << " ($"<<printing->get_id()
         << ')' << endl
         << "Birthday: ";
    format(printing->birthday());
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
        format((*it)->get_begin());
        cout << ")-(";
        format((*it)->get_end());
        cout << ")]" << endl;
    }
}

