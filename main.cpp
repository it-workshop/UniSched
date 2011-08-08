#include <iostream>
#include <time.h>

#include <usersinterface.h>
#include <person.h>
#include <group.h>
#include <event.h>

int main (int argc, char *argv[])
{
    Person new_Person0("Prihodko", "Ivan"),
           new_Person1("Derbenev", "Alexander"),
           new_Person2("Nam", "Lusia");
    Group new_group0("0-group"),
          new_group1("1-group"),
          new_group2("2-group");
    Event new_event0("event0", time(0), time(0) + 5000),
          new_event1("event1", time(0) + 10000, time(0) + 15000);
    
    UsersInterface ui;

    new_group1.add_Person(&new_Person0);
    new_group2.add_Person(&new_Person0);
    new_group1.add_Person(&new_Person1);

    new_Person0.add_Event(&new_event0);
    new_Person0.add_Event(&new_event1);

    ui.out_Person(&new_Person0);
    ui.out_Person(&new_Person1);
    ui.out_Person(&new_Person2);
    
    ui.out_Group(&new_group0);
    ui.out_Group(&new_group1);
    ui.out_Group(&new_group2);

    ui.out_Event(&new_event0);
    ui.out_Event(&new_event1);

    return 0;
}

