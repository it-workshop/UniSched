#include <iostream>
#include <time.h>
#include <vector>

#include <types.h>
#include <commands.h>
#include <userinterface.h>
#include <person.h>
#include <group.h>
#include <event.h>
#include <data_storage.h>

int main (int argc, char *argv[])
{
    std::vector<string> args;

    storage::DataStorage *db = new storage::FileStorage ();
    db->setup ("database/", "", "", "");
    db->load ();
    db->init ();

    for (int i = 1; i < argc; i++)
        args.push_back(argv[i]);

    UserInterface *ui = new UserInterface ();

    uiconsole::initiate(ui);
    
    if (argc - 1)
        uiconsole::execute(args);
    else
        ui->listen();

    return 0;
}

