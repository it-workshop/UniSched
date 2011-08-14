#include <commands.h>

vector<uiconsole::Command *> commands;

uiconsole::Command::Command(UserInterface *ui)
{
    this->ui = ui;
    commands.push_back(this);
}

uiconsole::Command::~Command()
{
    for (vector<uiconsole::Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
    {
        if (*it == this)
        {
            it = commands.erase(it);
            return;
        }
    }
}

string uiconsole::Command::get_name()
{
    return name;
}

string uiconsole::Command::get_description()
{
    return description;
}

string uiconsole::Command::get_help()
{
    return help;
}

uiconsole::Command_Exit::Command_Exit(UserInterface *ui): uiconsole::Command (ui)
{
    name = "exit";
    description = "exit from programm.";
    help = "Type ,,exit`` to exit from programm.";
}

void uiconsole::Command_Exit::run(vector<string> args)
{
    cout << endl;
    ui->exit();
}

uiconsole::Command_All::Command_All(UserInterface *ui): uiconsole::Command (ui)
{
    name = "all";
    description = "print all objects of a kind ($ @ # %%).";
    help = "Type ,,all s`` to print all objects of a kind s, where s = $ - people, @ - groups, # - events, %% - calendars.";
}

void uiconsole::Command_All::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for all." << endl;
        return;
    }
    char symbol = args[1][0];
    switch (symbol)
    {
    case '$':
        for (vector<Person *>::iterator it = ui->people->begin(); it != ui->people->end(); it ++)
            ui->print_person(*it);
        break;
    case '@':
        for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            ui->print_group(*it);
        break;
    case '#':
        for (vector<Event *>::iterator it = ui->events->begin(); it != ui->events->end(); it ++)
            ui->print_event(*it);
        break;
    case '%':
        for (vector<Calendar *>::iterator it = ui->calendars->begin(); it != ui->calendars->end(); it ++)
            ui->print_calendar(*it);
        break;
    default:
        cout << "Only person, group, event and calendar can be printed." << endl;
    } 
}

uiconsole::Command_Print::Command_Print(UserInterface *ui): uiconsole::Command (ui)
{
    name = "print";
    description = "print one object by id.";
    help = "Type ,,print (s)(id)`` to print object of a class s, and id id.";
}

void uiconsole::Command_Print::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for print." << endl;
        return;
    }
    char symbol = args[1][0];
    id_type id = atoll(args[1].c_str() + 1);
    switch (symbol)
    {
    case '$':
        for (vector<Person *>::iterator it = ui->people->begin(); it != ui->people->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_person(*it);
                return;
            }
        cout << "There're no person with that id.";
        break;
    case '@':
        for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_group(*it);
                return;
            }
        cout << "There're no group with that id.";
        break;
    case '#':
        for (vector<Event *>::iterator it = ui->events->begin(); it != ui->events->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_event(*it);
                return;
            }
        cout << "There're no event with that id.";
        break;
    case '%':
        for (vector<Calendar *>::iterator it = ui->calendars->begin(); it != ui->calendars->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_calendar(*it);
                return;
            }
        cout << "There're no calendar with that id.";
        break;
    default:
        cout << "Only person, group, event and calendar can be printed." << endl;
    }
}

uiconsole::Command_Clone::Command_Clone(UserInterface *ui) : Command(ui)
{
    name = "clone";
    description = "clone one object by id.";
    help = "Type ,,clone (s)(id)`` to clone object of a class s, and id id.";
}

void uiconsole::Command_Clone::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for clone." << endl;
        return;
    }
    char symbol = args[1][0];
    id_type id = atoll(args[1].c_str() + 1);
    switch (symbol)
    {
    case '@':
        for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            if ((*it)->get_id() == id)
            {
                Group *newbie = new Group(ui->groups->size(), (*it));
                ui->groups->push_back(newbie); ////////////////////////////////////////////
                ui->print_group(newbie);
                return;
            }
        cout << "There're no group with that id.";
        break;
    case '%':
         for (vector<Calendar *>::iterator it = ui->calendars->begin(); it != ui->calendars->end(); it ++)
            if ((*it)->get_id() == id)
            {
                Calendar *newbie = new Calendar(ui->calendars->size(), (*it));
                ui->calendars->push_back(newbie); //////////////////////////////////////
                ui->print_calendar(newbie);
                return;
            }
        cout << "There're no calendar with that id.";
        break;
    }
}

uiconsole::Command_Merge::Command_Merge(UserInterface *ui) : Command(ui)
{
    name = "merge";
    description = "merges two objects by id's.";
    help = "Type ,,merge (s)(id0) (s)(id1) to merge two objects of a class s, with id's id0 and id1.";
}

void uiconsole::Command_Merge::run(vector<string> args)
{
    if (args.size() < 3)
    {
        cout << "Need two arguments for merge." << endl;
        return;
    }
    char symbol = args[1][0];
    if ((args[2][0] != '@') || (args[1][0] != '@'))
    {
        cout << "Arguments must be groups." << endl;
        return;
    }
    id_type id0 = atoll(args[1].c_str() + 1);
    id_type id1 = atoll(args[2].c_str() + 1);
    Group *group0, *group1;
    for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
    {
        if ((*it)->get_id() == id0)
            group0 = *it;
        if ((*it)->get_id() == id1)
            group1 = *it;
    }
    if ((group0) && (group1))
    {
        group0->merge_group(group1);
        ui->print_group(group0);
    }
    else
        cout << "There're no group with that id.";
}

void uiconsole::execute(vector<string> args)
{
    for (vector<uiconsole::Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
        if ((*it)->get_name() == args[0])
        {
            (*it)->run(args);
            return;
        }
    cout << endl << "There's no function named: " << args[0] << endl;
}

void uiconsole::initiate(UserInterface *ui)
{
    new uiconsole::Command_Exit(ui);
    new uiconsole::Command_All(ui);
    new uiconsole::Command_Print(ui);
    new uiconsole::Command_Clone(ui);
    new uiconsole::Command_Merge(ui);
}

