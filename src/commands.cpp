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
    help = "Print ,,exit`` to exit from programm.";
}

void uiconsole::Command_Exit::run(vector<string> args)
{
    ui->exit();
}

uiconsole::Command_All::Command_All(UserInterface *ui): uiconsole::Command (ui)
{
    name = "all";
    description = "print all objects of a kind ($ @ # %%).";
    help = "Print ,,all s`` to print all objects of a kind s, where s = $ - people, @ - groups, # - events, %% - calendars.";
}

void uiconsole::Command_All::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for all" << endl;
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
        cout << "Only person, group, event and calendar can be printed" << endl;
    } 
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
}

