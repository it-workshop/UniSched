#include <commands.h>

uiconsole::Command_Print::Command_Print(UserInterface *ui): uiconsole::Command (ui)
{
    name = "print";
    description = "print one object by id.";
    help = "Type ,,print (s)(id)`` to print object of a class s, and id id.";
}

void uiconsole::Command_Print::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for print." << endl;
        return;
    }
    char symbol = args[1][0];
    id_type id = atoll(args[1].c_str() + 1);
    switch (symbol)
    {
    case '$':
        for (vector<Person *>::iterator it = ui->people->begin(); it != ui->people->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_person(*it);
                return;
            }
        cout << "There're no person with that id.";
        break;
    case '@':
        for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_group(*it);
                return;
            }
        cout << "There're no group with that id.";
        break;
    case '#':
        for (vector<Event *>::iterator it = ui->events->begin(); it != ui->events->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_event(*it);
                return;
            }
        cout << "There're no event with that id.";
        break;
    case '%':
        for (vector<Calendar *>::iterator it = ui->calendars->begin(); it != ui->calendars->end(); it ++)
            if ((*it)->get_id() == id)
            {
                ui->print_calendar(*it);
                return;
            }
        cout << "There're no calendar with that id.";
        break;
    default:
        cout << "Only person, group, event and calendar can be printed." << endl;
    }
}

