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

namespace storage{

enum Errors {
    NO_ERR,
    SET_CELL_VALUE_ERR,
    GET_CELL_VALUE_ERR,
    UNKOWN_ERR,
    LOAD_ERR,
    SAVE_ERR
};

using std::string;
using std::vector;
using std::sort;

enum PersonAttribute {
    paNAME = 1,
    paSURNAME,
    paBIRTHDAY,
    paSEX
};

enum GroupAttribute {
    gaNAME = 1,
    gaDESCRIPTION,
    gaCALENDAR
};

enum EventAttribute {
    eaNAME = 1,
    eaGROUP,
    eaBEGIN, 
    eaEND,
    eaDESCRIPTION
};

typedef struct CalendarBunch_ {
    id_type ID;
    id_type EventID;
} CalendarBunch;

typedef struct GroupBunch_ {
    id_type PersonID;
    id_type GroupID;
    string Status;
} GroupBunch;

typedef struct dsrow_ {
    vector<string> fields;
} dsrow;

class TableDataStorage {
public:
     TableDataStorage();
    ~TableDataStorage();

    void create_table(int fields_count);

    void add_row(string fields[]);
    void rem_row(int row);

    string get_cell_value(int row, int field);
    bool set_cell_value(int row, int field, string value);

    Errors get_last_error();

    bool load_table(string filename);
    bool save_table(string filename);

    bool load_table(string host, string user, string pass, string bdname);
    bool save_table(string host, string user, string pass, string bdname);

    unsigned long long int get_rows_count();
    unsigned long long int get_fields_count();

private:
    int fields_count_;
    int rows_count_;

    Errors error_;

    vector<dsrow> rows_;
};

class DataStorage{
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

    Person * get_person (id_type id);
    Group * get_group (id_type id);
    Event * get_event (id_type id);
    Calendar * get_calendar (id_type id);

    void register_group (Group *group);
    void register_calendar (Calendar *calendar);
    void register_person (Person *person);
    void register_event (Event *event);

private:
    vector<id_type> get_person_ID_list();

    string get_person_attr(PersonAttribute attr, id_type id);
    void set_person_attr(PersonAttribute attr, id_type id, string value);

    void add_person(id_type id);
    void remove_person(id_type id);

    vector<id_type> get_group_ID_list();

    string get_group_attr(GroupAttribute attr, id_type id);
    void set_group_attr(GroupAttribute attr, id_type id, string value);

    void add_group(id_type id);
    void remove_group(id_type id);

    vector<id_type> get_event_ID_list();

    string get_event_attr(EventAttribute attr, id_type id);
    void set_event_attr(EventAttribute attr, id_type id, string value);

    void add_event(id_type id);
    void remove_event(id_type id);

    unsigned long long int get_calendar_bunches_count();
    CalendarBunch get_calendar_bunch(unsigned long long int num);
    void remove_calendar_bunch(unsigned long long int num);
    void add_calendar_bunch(CalendarBunch bnch);

    unsigned long long int get_group_bunches_count();
    GroupBunch get_group_bunch(unsigned long long int num);
    void remove_group_bunch(unsigned long long int num);
    void add_group_bunch(GroupBunch bnch);

    vector<Person *> people_vector_;
    vector<Group *> groups_vector_;
    vector<Event *> events_vector_;
    vector<Calendar *> calendars_vector_;

    protected:
    TableDataStorage people_;
    TableDataStorage groups_;
    TableDataStorage events_;
    TableDataStorage group_content_;
    TableDataStorage calendars_;
};

class FileStorage : public DataStorage{
public:
     FileStorage ();
    ~FileStorage ();
    void setup(string location, string user, string password, string bdname);
    bool load();
    bool save();
private:
    string path_;
};

};

#endif /* _DATASTORAGE_H_ */

