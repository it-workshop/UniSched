#include <iostream>
#include <time.h>
#include <vector>

#include <usersinterface.h>
#include <person.h>
#include <group.h>
#include <event.h>

int main (int argc, char *argv[])
{
    std::vector<Person *> persons;
    std::vector<Group *> groups;
    std::vector<Event *> events;
    std::vector<Calendar *> calendars;
    /*Person new_Person0("Prihodko", "Ivan"),
           new_Person1("Derbenev", "Alexander"),
           new_Person2("Nam", "Lusia");
    Group new_group0("0-group"),
          new_group1("1-group"),
          new_group2("2-group");
    Event new_event0("event0", time(0), time(0) + 5000),
          new_event1("event1", time(0) + 10000, time(0) + 15000);
    */

    persons.push_back(new Person("Prihodko", "Ivan"));
    persons.push_back(new Person("Derbenev", "Alexander"));
    persons.push_back(new Person("Nam", "Lusia"));

    groups.push_back(new Group("0-group"));
    groups.push_back(new Group("1-group"));
    groups.push_back(new Group("2-group"));

    events.push_back(new Event("event0", time(0), time(0) + 5000));
    events.push_back(new Event("event1", time(0) + 10000, time(0) + 15000));
    events.push_back(new Event("event2", time(0) - 10000, time(0) - 5000));

    UsersInterface ui;

    groups[1]->add_Person(persons[0]);
    groups[2]->add_Person(persons[0]);
    groups[1]->add_Person(persons[1]);

    persons[0]->add_Event(events[0]);
    persons[0]->add_Event(events[1]);

    ui.out_Person(persons[0]);
    ui.out_Person(persons[1]);
    ui.out_Person(persons[2]);
    
    ui.out_Group(groups[0]);
    ui.out_Group(groups[1]);
    ui.out_Group(groups[2]);

    ui.out_Event(events[0]);
    ui.out_Event(events[1]);
    ui.out_Event(events[2]);

    return 0;
}

