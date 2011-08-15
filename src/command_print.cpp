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
        if (ui->get_db ()->get_person (id))
	    ui->print_person (ui->get_db ()->get_person (id));
	else
            cout << "There're no person with that id.";
        break;
    case '@':
        if (ui->get_db ()->get_group (id))
            ui->print_group(ui->get_db ()->get_group (id));
        else
            cout << "There're no group with that id.";
        break;
    case '#':
        if (ui->get_db ()->get_event (id))
            ui->print_event(ui->get_db ()->get_event (id));
	else
            cout << "There're no event with that id.";
        break;
    case '%':
        if (ui->get_db ()->get_calendar (id))
            ui->print_calendar(ui->get_db ()->get_calendar (id));
	else
            cout << "There're no calendar with that id.";
        break;
    default:
        cout << "Only person, group, event and calendar can be printed." << endl;
    }
}

