#include <commands.h>

uiconsole::Command_Add::Command_Add(UserInterface *ui) : Command(ui)
{
    name = "add";
    description = "add new object";
    help = "Type ,,add @(name)`` and description ended with empty string to add group,\n" \
           "Type ,,add $(name) (surname) (sex) DD/MM/YYYY(birthday) to add person,\n" \
           "Type ,,add #(name) HH:MM-DD/MM/YYYY(begin) HH:MM-DD/MM/YYYY(end) and description ended with empty string to add event,\n" \
           "Type ,,add &(name) to add new queue.";
}

void uiconsole::Command_Add::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need type for add." << endl;
        return;
    }
    char symbol = args[1][0];
    string name, description;
    time_t begin, end;
    Group *new_group;
    Person *new_person;
    Event *new_event;
    switch (symbol)
    {
    case '@':
        name = args[1].c_str() + 1;
        cout << "Input description of the group" << endl;
        while (symbol != '\n')
        {
            symbol = getchar();
            description += symbol;
            if (symbol == '\n')
                symbol = getchar();
        }
        new_group = new Group(ui->groups->size(), name, description);
        ui->groups->push_back(new_group);
        ui->print_group(new_group);
        break;
    case '$':
        if (args.size() < 5)
        {
            cout << "Need more arguments, see ,,help add``." << endl;
            return;
        }
        name = args[1].c_str() + 1;
        begin = ui->get_birthday(args[4]);
	if (!begin)
        {
            cout << "Poor date format" << endl;
            return;
        }
        new_person = new Person(ui->people->size(), name, args[2], (args[3] == "MALE") ? Person::MALE : Person::FEMALE, begin);
        ui->people->push_back(new_person);
        ui->print_person(new_person);
        break;
    case '#':
        if (args.size() < 4)
        {
            cout << "Need more arguments, see ..help add``." << endl;
        }
        name = args[1].c_str() + 1;
        begin = ui->get_time(args[2]);
        end = ui->get_time(args[3]);
        if ((!begin) || (!end))
        {
            cout << "Poor time format" << endl;
            return;
        }
        cout << "Input description of the event" << endl;
        while (symbol != '\n')
        {
            symbol = getchar();
            description += symbol;
            if (symbol == '\n')
                symbol = getchar();
        } 
        new_event = new Event(ui->events->size(), name, begin, end, description);
        ui->events->push_back(new_event);
        ui->print_event(new_event);
        break;
    default:
        cout << "Only people, groups and events can be added.";
    }
}

