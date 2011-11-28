#include "commands.h"

uiconsole::Command_Select::Command_Select(UserInterface *ui) : Command(ui)
{
    name = "select";
    description = "select group from group";
    help = "Type ,,select @(id0) @(id1) (N) &(id2)`` to include N people from id0 to id1.";
}

void uiconsole::Command_Select::run(vector<string> args)
{
    srand(time(0));
    if (args.size() < 5)
    {
        cout << "Need four arguments." << endl;
        return;
    }
    if ((args[1][0] != '@') || (args[2][0] != '@') || (args[4][0] != '&'))
    {
        cout << "Wrong types." << endl;
        return;
    }
    id_type id0 = atoll(args[1].c_str() + 1),
            id1 = atoll(args[2].c_str() + 1),
            id2 = atoll(args[4].c_str() + 1);
    int N = atoi(args[3].c_str());
    Group *input = ui->get_db()->get_group(id0),
          *output = ui->get_db()->get_group(id1);
    Queue *queue = ui->get_db()->get_queue(id2);
    while (input->get_people()->size() < N)
        if (queue->get_vector()->empty())
        {
            cout << "RTFM" << endl;
            return;
        }
            input->merge_group(queue->dequeue());
    Group *copy = new Group(input);
    for (int i = 0; i < N; i++)
    {
        int b = 0, a = rand() % copy->get_people()->size();
        vector<Group_Content *>::iterator it;
        for (it = copy->get_people()->begin(); b < a; it ++)
            b++;
        output->add_person((*it)->person, "auto");
        copy->get_people()->erase(it);
    }
}

