#include "commands.h"

uiconsole::Command_Enqueue::Command_Enqueue(UserInterface *ui) : Command(ui)
{
    name = "enqueue";
    description = "enqueue group into queue";
    help = "Type ,,enqueue &(id0) @(id1)`` to enqueue group id1 into queue id0.";
}

void uiconsole::Command_Enqueue::run(vector<string> args)
{
    if (args.size() < 3)
    {
        cout << "Need two arguments." << endl;
        cout << this->help;
        return;
    }
    if ((args[1][0] != '&') || (args[2][0] != '@'))
    {
        cout << "Wrong types." << endl;
        cout << this->help;
        return;
    }
    id_type id0 = atoll(args[1].c_str() + 1),
            id1 = atoll(args[2].c_str() + 1);
    ui->get_db()->get_queue(id0)->enqueue(ui->get_db()->get_group(id1));
}

