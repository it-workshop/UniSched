#include <commands.h>

uiconsole::Command_Link::Command_Link(UserInterface *ui) : Command(ui)
{
    name = "link";
    description = "link two objects";
    help = "Type ,,link @(id0) $(id1) (status)`` to link group id0 with person id1,\n" \
           "Type ,,link $(id0) #(id1) (status)`` to link person id0 with event id1,\n" \
           "Type ,,link #(id0) @(id1) (status)`` to link event id0 with group id1.";
}

void uiconsole::Command_Link::run(vector<string> args)
{
    if (args.size() < 4)
    {
        cout << "Need type for link." << endl;
        return;
    }
    char symbol0 = args[1][0],
         symbol1 = args[2][0];
    id_type id0 = atoll(args[1].c_str() + 1);
    id_type id1 = atoll(args[2].c_str() + 1);
    Group *group;
    Person *person;
    Event *event;
    switch (symbol0)
    {
    case '@':
        if (symbol1 != '$')
        {
            cout << "Wrong arguments, see ,,help link``." << endl;
            return;
        }
        for (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            if ((*it)->get_id() == id0)
                group = *it;
        for  (vector<Person *>::iterator it = ui->people->begin(); it != ui->people->end(); it ++)
            if ((*it)->get_id() == id1)
                person = *it;
        if ((!group) || (!person))
        {
            cout << "Wrong id" << endl;
            return;
        }
        group->add_person(person, args[3]);
        ui->print_group(group);
        ui->print_person(person);
        break;
    case '$':
        if (symbol1 != '#')
        {
            cout << "Wrong arguments, see ,,help link``.";
            return;
        }
        for (vector<Person *>::iterator it = ui->people->begin(); it != ui->people->end(); it ++)
            if ((*it)->get_id() == id0)
                person = *it;
        for  (vector<Event *>::iterator it = ui->events->begin(); it != ui->events->end(); it ++)
            if ((*it)->get_id() == id1)
                event = *it;
        if ((!event) || (!person))
        {
            cout << "Wrong id" << endl;
            return;
        }
        person->add_event(event, args[3]);
        ui->print_person(person);
        ui->print_event(event);
        break;
    case '#':
        if (symbol1 != '@')
        {
            cout << "Wrong arguments, see ,,help link``.";
            return;
        }
        for (vector<Event *>::iterator it = ui->events->begin(); it != ui->events->end(); it ++)
            if ((*it)->get_id() == id0)
                event = *it;
        for  (vector<Group *>::iterator it = ui->groups->begin(); it != ui->groups->end(); it ++)
            if ((*it)->get_id() == id1)
                group = *it;
        if ((!group) || (!event))
        {
            cout << "Wrong id" << endl;
            return;
        }
        group->add_event(event, args[3]);
        ui->print_event(event);
        ui->print_group(group);
        break;
    default:
        cout << "Wrong arguments, see ,,help link``.";
    }
}

