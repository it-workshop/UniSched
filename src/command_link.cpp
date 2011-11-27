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
        
	group = ui->get_db ()->get_group (id0);
        person = ui->get_db ()->get_person (id1);

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

        person = ui->get_db ()->get_person (id0);
        event = ui->get_db ()->get_event (id1);

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
        
	event = ui->get_db ()->get_event (id0);
        group = ui->get_db ()->get_group (id1);

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

