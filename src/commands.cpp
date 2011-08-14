#define _COMMANDS_CPP_
#include <commands.h>

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
    new uiconsole::Command_Help(ui);
    new uiconsole::Command_Clone(ui);
    new uiconsole::Command_Merge(ui);
    new uiconsole::Command_Exclude(ui);
    new uiconsole::Command_Include(ui);
    new uiconsole::Command_Add(ui);
    new uiconsole::Command_Link(ui);
}

