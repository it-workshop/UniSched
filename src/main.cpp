#include <iostream>
#include <time.h>
#include <vector>

#include "types.h"
#include "event_template.h"
#include "queue.h"
#include "commands.h"
#include "userinterface.h"
#include "person.h"
#include "group.h"
#include "event.h"
#include "data_storage.h"
#include "file_storage.h"

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
    ui->set_db (db);

    uiconsole::initiate(ui);
    
//    Event_Template *test = new Event_Template("all $\nall @\nall %\nall #\nexit\n", 12);

//    test->get_requered_people();

    if (argc - 1)
        uiconsole::execute(args);
    else
        ui->listen();

    db->sync ();
    db->save ();

    return 0;
}

