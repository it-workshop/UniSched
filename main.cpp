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

    persons.push_back(new Person("p000", "Prihodko", "Ivan", false, time(0) - 1000000));
    persons.push_back(new Person("p001", "Derbenev", "Alexander", false, time(0) - 1500000));
    persons.push_back(new Person("p002", "Nam", "Lusia", true, time(0) - 2000000));

    groups.push_back(new Group("g000", "0-group", "blah-blah-blah0"));
    groups.push_back(new Group("g001", "1-group", "blah-blah-blah1"));
    groups.push_back(new Group("g002", "2-group", "blah-blah_blah2"));

    events.push_back(new Event("e000", "event0", time(0), time(0) + 5000, "blah-blah0"));
    events.push_back(new Event("e001", "event1", time(0) + 10000, time(0) + 15000, "blah-blah1"));
    events.push_back(new Event("e002", "event2", time(0) - 10000, time(0) - 5000, "blah-blah2"));

    UsersInterface ui;

    groups[1]->add_Person(persons[0]);
    groups[2]->add_Person(persons[0]);
    groups[1]->add_Person(persons[1]);

    persons[0]->add_Event(events[0]);
    persons[0]->add_Event(events[1]);

    ui.print_Person(persons[0]);
    ui.print_Person(persons[1]);
    ui.print_Person(persons[2]);
    
    ui.print_Group(groups[0]);
    ui.print_Group(groups[1]);
    ui.print_Group(groups[2]);

    ui.print_Event(events[0]);
    ui.print_Event(events[1]);
    ui.print_Event(events[2]);

    return 0;
}

