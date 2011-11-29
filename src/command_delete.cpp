#include "commands.h"

uiconsole::Command_Delete::Command_Delete(UserInterface *ui) : Command(ui)
{
    name = "delete";
    description = "delete object.";
    help = "Type ,,delete (s)(id)`` to delete object of class (s) and id (id).";
}

void uiconsole::Command_Delete::run(vector<string> args)
{
    if (args.size() == 1)
    {
        cout << "Need argument for delete." << endl;
        cout << this->help;
        return;
    }
    char symbol = args[1][0];
    if (args[1].size() == 1)
    {
        cout << "Need id or name after (s)." << endl;
        cout << this->help;
    }
    id_type id = atoll(args[1].c_str() + 1);
    string name = "";
    if ((!id) && (args[1][1] != '0'))
        name = args[1].c_str() + 1;
    else
    {
        switch (symbol)
        {
        case '$':
            ui->get_db()->delete_person(id);
            break;
        case '@':
            ui->get_db()->delete_group(id);
            break;
        case '#':
            ui->get_db()->delete_event(id);
            break;
        case '&':
            ui->get_db()->delete_queue(id);
            break;
        default:
            cout << "Input class correctly." << endl;
        }
    }
}

