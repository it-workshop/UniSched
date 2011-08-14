#include <commands.h>

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

