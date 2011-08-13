#include <iostream>
#include <time.h>
#include <vector>

#include <types.h>
#include <userinterface.h>
#include <person.h>
#include <group.h>
#include <event.h>

int main (int argc, char *argv[])
{
    std::vector<Person *> persons;
    std::vector<Group *> groups;
    std::vector<Event *> events;
    std::vector<Calendar *> calendars;

    persons.push_back(new Person(0, "Prihodko", "Ivan", false, time(0) - 1000000));
    persons.push_back(new Person(1, "Derbenev", "Alex", false, time(0) - 1500000));
    persons.push_back(new Person(2, "Nam", "Lusia", true, time(0) - 2000000));

    groups.push_back(new Group(0, "0-group", "blah-blah-blah0"));
    groups.push_back(new Group(2, "1-group", "blah-blah-blah1"));
    groups.push_back(new Group(4, "2-group", "blah-blah_blah2"));

    events.push_back(new Event(0, "event0", time(0), time(0) + 5000, "blah-blah0"));
    events.push_back(new Event(1, "event1", time(0) + 10000, time(0) + 15000, "bla1"));
    events.push_back(new Event(2, "event2", time(0) - 10000, time(0) - 5000, "blah2"));

    UserInterface ui(&persons, &groups, &events, &calendars);

    groups[1]->add_person(persons[1], "director");
    groups[1]->add_person(persons[0], "wizard");
    groups[2]->add_person(persons[0], "member");
    groups[2]->add_person(persons[2], "director");

    persons[0]->add_event(events[2], "director");
    groups[1]->add_event(events[2]);
    
    persons[0]->add_event(events[0], "director");
    persons[0]->add_event(events[1], "director");

    ui.listen();
    return 0;
}

