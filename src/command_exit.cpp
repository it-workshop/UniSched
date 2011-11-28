#include "commands.h"

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


