#include "commands.h"

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
        if (ui->get_db ()->get_group (id))
        {
            Group *newbie = new Group(ui->get_db ()->get_group (id));
            ui->get_db ()->register_group(newbie); ////////////////////////////////////////////
            ui->print_group(newbie);
            return;
        }
        cout << "There're no group with that id.";
        break;
    case '%':
         if (ui->get_db ()->get_calendar (id))
         {
             Calendar *newbie = new Calendar(ui->get_db ()->get_calendar (id));
             ui->get_db ()->register_calendar(newbie); //////////////////////////////////////
             ui->print_calendar(newbie);
             return;
         }
        cout << "There're no calendar with that id.";
        break;
    }
}

