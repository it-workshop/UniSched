#include "commands.h"

uiconsole::Command_All::Command_All(UserInterface *ui): uiconsole::Command (ui)
{
    name = "all";
    description = "print all objects of a kind ($ @ # %%).";
    help = "Type ,,all s`` to print all objects of a kind s, where s = $ - people, @ - groups, # - events, %% - calendars.";
}

void uiconsole::Command_All::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need one argument for all." << endl;
        return;
    }
    char symbol = args[1][0];
    switch (symbol)
    {
    case '$':
        for (vector<Person *>::iterator it = ui->get_db ()->get_people ()->begin(); it != ui->get_db ()->get_people ()->end(); it ++)
            ui->print_person(*it);
        break;
    case '@':
        for (vector<Group *>::iterator it = ui->get_db ()->get_groups ()->begin(); it != ui->get_db ()->get_groups ()->end(); it ++)
            ui->print_group(*it);
        break;
    case '#':
        for (vector<Event *>::iterator it = ui->get_db ()->get_events ()->begin(); it != ui->get_db()->get_events ()->end(); it ++)
            ui->print_event(*it);
        break;
    case '%':
        for (vector<Calendar *>::iterator it = ui->get_db ()->get_calendars ()->begin(); it != ui->get_db ()->get_calendars ()->end(); it ++)
            ui->print_calendar(*it);
        break;
    default:
        cout << "Only person, group, event and calendar can be printed." << endl;
    } 
}


