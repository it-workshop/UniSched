#include "commands.h"

uiconsole::Command_Include::Command_Include(UserInterface *ui) : Command(ui)
{
    name = "include";
    description = "include two groups by id's";
    help = "Type ,,include @(id0) @(id1)`` to include group id1 and group id0.";
}

void uiconsole::Command_Include::run(vector<string> args)
{
    if (args.size() < 3)
    {
        cout << "Need two arguments for merge." << endl;
        cout << this->help;
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

    group0 = ui->get_db ()->get_group (id0);
    group1 = ui->get_db ()->get_group (id1);

    if ((group0) && (group1))
    {
        group0->include_group(group1);
        ui->print_group(group0);
    }
    else
        cout << "There're no group with that id.";
}

