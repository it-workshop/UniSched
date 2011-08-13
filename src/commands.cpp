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
    description = "print all objects of a kind ($ @ # %).";
    help = "Print ,,all s`` to print all objects of a kind s, where s = $ - people, @ - groups, # - events, % - calendars.";
}

void uiconsole::Command_All::run(vector<string> args)
{
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

uiconsole::Command_Help::Command_Help(UserInterface *ui): uiconsole::Command(ui)
{
    name = "help";
    description = "print help to command or descriptions of all commands.";
    help = "Print ,,help`` to print descriptoins or print ,,help command`` to get more detalized information about command.";
}

void uiconsole::Command_Help::run(vector<string> args)
{
    if (args.size() == 1)
    {
        for (vector<uiconsole::Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
            cout << (*it)->get_name() << " : " << (*it)->get_description() << endl;
        return;
    }
    else
        for (vector<uiconsole::Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
            if ((*it)->get_name() == args[1])
            {
                cout << (*it)->get_help() << endl;
                return;
            }
    cout << endl << "There's no function named: " << args[1] << endl;
}

void uiconsole::execute(vector<string> args)
{
    for (vector<uiconsole::Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
        if ((*it)->get_name() == args[0])
        {
            (*it)->run(args);
            return;
        }
    if (args[0] != "Ctrl+D")
        cout << endl << "There's no function named: " << args[0];
    cout << endl;
}

void uiconsole::initiate(UserInterface *ui)
{
    new uiconsole::Command_Exit(ui);
    new uiconsole::Command_All(ui);
    new uiconsole::Command_Help(ui);
}

