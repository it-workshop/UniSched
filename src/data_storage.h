#ifndef _DATASTORAGE_H_
#define _DATASTORAGE_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include <types.h>
#include <person.h>
#include <group.h>
#include <event.h>
#include <calendar.h>
#include <queue.h>
#include <event_template.h>
#include <table_data_storage.h>

using std::string;
using std::vector;
using std::sort;

struct storage::CalendarBunch_ {
    id_type ID;
    id_type EventID;
};

struct storage::GroupBunch_ {
    id_type PersonID;
    id_type GroupID;
    string Status;
};

struct storage::QueueBunch_ {
    id_type QueueID;
    id_type GroupID;
};

class storage::DataStorage{
public:
     DataStorage ();
    ~DataStorage ();

    virtual bool load() = 0;
    virtual bool save() = 0;
    void init ();

    virtual void setup(string location, string user, string pass, string bdname) = 0;
    vector<Person *> *get_people ();
    vector<Group *> *get_groups ();
    vector<Event *> *get_events ();
    vector<Calendar *> *get_calendars ();
    vector<Queue *> *get_queues ();
    vector<Event_Template *> *get_event_templates ();



    Person * get_person (id_type id);
    Group * get_group (id_type id);
    Event * get_event (id_type id);
    Calendar * get_calendar (id_type id);
    Queue * get_queue (id_type id);
    Event_Template * get_event_template (id_type id);

    void delete_group (id_type id);
    void delete_calendar (id_type id);
    void delete_person (id_type id);
    void delete_event (id_type id);
    void delete_queue (id_type id);
    void delete_event_template (id_type id);


    void register_group (Group *group);
    void register_calendar (Calendar *calendar);
    void register_person (Person *person);
    void register_event (Event *event);
    void register_queue (Queue *queue);
    void register_event_template (Event_Template *event_template);

private:

    string get_person_attr(PersonAttribute attr, id_type id);
    void set_person_attr(PersonAttribute attr, id_type id, string value);

    void add_person(id_type id);
    void remove_person(id_type id);

    string get_group_attr(GroupAttribute attr, id_type id);
    void set_group_attr(GroupAttribute attr, id_type id, string value);

    void add_group(id_type id);
    void remove_group(id_type id);

        string get_event_attr(EventAttribute attr, id_type id);
    void set_event_attr(EventAttribute attr, id_type id, string value);

    void add_event(id_type id);
    void remove_event(id_type id);

    vector<id_type> get_person_ID_list();
    vector<id_type> get_group_ID_list();
    vector<id_type> get_event_ID_list();
    vector<id_type> get_event_template_ID_list ();

    string get_event_template_attr (EventTemplateAttribute attr, id_type id);
    void set_event_template_attr (EventTemplateAttribute attr, id_type id, string value);

    void add_event_template (id_type id);
    void remove_event_template (id_type id);

    vector<id_type> get_queue_ID_list ();

    void add_queue(id_type id);
    void remove_queue(id_type id);

    string get_queue_attr (QueueAttribute attr, id_type id);
    void set_queue_attr (QueueAttribute attr, id_type id, string value);

    unsigned long long int get_calendar_bunches_count();
    CalendarBunch get_calendar_bunch(unsigned long long int num);
    void remove_calendar_bunch(unsigned long long int num);
    void add_calendar_bunch(CalendarBunch bnch);

    unsigned long long int get_group_bunches_count();
    GroupBunch get_group_bunch(unsigned long long int num);
    void remove_group_bunch(unsigned long long int num);
    void add_group_bunch(GroupBunch bnch);

    unsigned long long int get_queue_bunches_count();
    QueueBunch get_queue_bunch (unsigned long long int num);
    void remove_queue_bunch (unsigned long long int num);
    void add_queue_bunch (QueueBunch bnch);

    vector<Person *> people_vector_;
    vector<Group *> groups_vector_;
    vector<Event *> events_vector_;
    vector<Calendar *> calendars_vector_;
    vector<Queue *> queues_vector_;
    vector<Event_Template *> event_templates_vector_;

    protected:
    TableDataStorage people_;
    TableDataStorage groups_;
    TableDataStorage events_;
    TableDataStorage group_content_;
    TableDataStorage calendars_;
    TableDataStorage queues_;
    TableDataStorage queues_bunches_;
    TableDataStorage event_templates_;
};

#endif /* _DATASTORAGE_H_ */

