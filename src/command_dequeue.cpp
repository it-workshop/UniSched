#include "commands.h"

uiconsole::Command_Dequeue::Command_Dequeue(UserInterface *ui) : Command(ui)
{
    name = "dequeue";
    description = "dequeue group from queue";
    help = "Type ,,dequeue &(id0) @(id1)`` to dequeue group id1 from queue id0.";
}

void uiconsole::Command_Dequeue::run(vector<string> args)
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
    ui->get_db()->get_group(id1)->merge_group(ui->get_db()->get_queue(id0)->dequeue());
}

