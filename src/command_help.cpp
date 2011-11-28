#include "commands.h"

uiconsole::Command_Help::Command_Help(UserInterface *ui) : Command(ui)
{
    name = "help";
    description = "print descriptions or detialized help";
    help = "Type ,,help`` to print all descriptions, \n" \
           "Type ,,help (command)`` to print detialized help about command.";
}

void uiconsole::Command_Help::run(vector<string> args)
{
    if (args.size() == 1)
    {
        for (vector<Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
            cout << (*it)->get_name() << ":\t\t" << (*it)->get_description() << endl;
        return;
    }
    for (vector<Command *>::iterator it = commands.begin(); it != commands.end(); it ++)
        if ((*it)->get_name() == args[1])
        {
            cout << (*it)->get_help() << endl;
            return;
        }
    cout << "There're no funcion named:" << args[1];
}

