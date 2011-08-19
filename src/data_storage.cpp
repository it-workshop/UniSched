#include <data_storage.h>

using namespace storage;

string itos (unsigned long long int value)
{
    char array [21];
    char reverse [21];
    int i = 0;
    int length = 0;
    do
    {
        array [i++] = value % 10 + '0';
    }
    while ((value /= 10) > 0);
    length = i - 1;

    for (i = 0; i < length ; i++)
    {
        reverse [length - i] = array [i];
    }

    reverse [i] = '\0';
    return ((string) reverse);
}

unsigned long long int find_num_row(TableDataStorage table, id_type id)
{
    for (unsigned long long int i = 0; i < table.get_rows_count(); i++)
    {
        if (atoi(table.get_cell_value(i, 0).c_str ()) == id)
	{
            return i;
        }
    }

    return 0;
}

DataStorage::DataStorage ()
{
}

DataStorage::~DataStorage ()
{
}

bool less_calendar_id_comp (Group *group1, Group *group2)
{
    return (group1->get_calendar ()->get_id () < group2->get_calendar ()->get_id ());
}

bool less_id_comp(Group *group1, Group *group2)
{
    return group1->get_id() < group2->get_id();
}

inline unsigned long long int min (unsigned long long int a, unsigned long long int b)
{
    return (a < b)?a:b;
}

void DataStorage::init ()
{
    vector<id_type> persons_ids = get_person_ID_list ();
    vector<id_type> events_vector_ids = get_event_ID_list ();
    vector<id_type> groups_vector_ids = get_group_ID_list ();

    vector<Group *> owners;

    for (vector<id_type>::iterator it = persons_ids.begin (); it != persons_ids.end (); it++)
    {
        string name = get_person_attr (paNAME, *it);
	string surname = get_person_attr (paSURNAME, *it);
	enum Person::Sex sex = (get_person_attr (paSEX, *it) == "MALE")?Person::MALE:Person::FEMALE;
	time_t birthday = atoll(get_person_attr (paBIRTHDAY, *it).c_str ());

        people_vector_.push_back (new Person (*it, name, surname, sex, birthday));
    }

    for (vector<id_type>::iterator it = events_vector_ids.begin (); it != events_vector_ids.end (); it++)
    {
        string name = get_event_attr (eaNAME, *it);
	time_t begin = atoll (get_event_attr (eaBEGIN, *it).c_str ());
	time_t end = atoll (get_event_attr (eaEND, *it).c_str ());
	string description = get_event_attr (eaDESCRIPTION, *it);
	id_type group_id = atoll (get_event_attr (eaGROUP, *it).c_str ());

        events_vector_.push_back (new Event (*it, name, begin, end, description));
	events_vector_[events_vector_.size () - 1]->get_group ()->set_id (group_id);
	groups_vector_.push_back (events_vector_[events_vector_.size () - 1]->get_group ());
	calendars_vector_.push_back (groups_vector_[groups_vector_.size () - 1]->get_calendar ());
	owners.push_back (groups_vector_[groups_vector_.size () - 1]);
    }

    for (vector<id_type>::iterator it = groups_vector_ids.begin (); it != groups_vector_ids.end (); it++)
    {
        id_type calendar = atoll (get_group_attr (gaCALENDAR, *it).c_str ());
	string name;
	string description;

        for (vector<Group *>::iterator it_ = owners.begin (); it_ != owners.end (); it_++)
	{
	    if (*it == (*it_)->get_id ())
	    {
	        (*it_)->get_calendar ()->set_id (calendar);

	        goto skip;
	    }
	}

	name = get_group_attr (gaNAME, *it);
	description = get_group_attr (gaDESCRIPTION, *it);
        
        groups_vector_.push_back (new Group (*it, name, description));
	calendars_vector_.push_back (groups_vector_[groups_vector_.size () - 1]->get_calendar ());
	calendars_vector_[calendars_vector_.size () - 1]->set_id (calendar);
    skip:;
    }

    sort (groups_vector_.begin (), groups_vector_.end (), less_id_comp);

    for (unsigned long long int i = 0; i < get_group_bunches_count (); i++)
    {
        GroupBunch bunch = get_group_bunch (i);

	id_type j;
	for (j = min(bunch.GroupID, groups_vector_.size ());  groups_vector_[j]->get_id () != bunch.GroupID; j--);
	Group * group = groups_vector_[j];

	for (j = min(bunch.PersonID, people_vector_.size ()); people_vector_[j]->get_id () != bunch.PersonID; j--);
	Person * person = people_vector_[j];

	group->add_person (person, bunch.Status);
    }

    sort (groups_vector_.begin (), groups_vector_.end (), less_calendar_id_comp);

    for (unsigned long long int i = 0; i < get_calendar_bunches_count (); i++)
    {
        CalendarBunch bunch = get_calendar_bunch (i);

	id_type j;
	for (j = min(bunch.EventID, events_vector_.size ()); events_vector_[j]->get_id () != bunch.EventID; j--);
	Event *event = events_vector_[j];

	for (j = min(bunch.ID, groups_vector_.size ()); groups_vector_[j]->get_calendar ()->get_id () != bunch.ID; j--);
	groups_vector_[j]->add_event (event, "");
    }
}

vector<Person *> *DataStorage::get_people ()
{
    return &people_vector_;
}

vector<Group *> *DataStorage::get_groups ()
{
    return &groups_vector_;
}

vector<Event *> *DataStorage::get_events ()
{
    return &events_vector_;
}

vector<Calendar *> *DataStorage::get_calendars ()
{
    return &calendars_vector_;
}

vector<Queue *> *DataStorage::get_queues ()
{
    return &queues_vector_;
}

vector<Event_Template *> *DataStorage::get_event_templates ()
{
    return &event_templates_vector_;
}

Person * DataStorage::get_person (id_type id)
{
    for (vector<Person *>::iterator it = people_vector_.begin (); it != people_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

Group * DataStorage::get_group (id_type id)
{
    for (vector<Group *>::iterator it = groups_vector_.begin (); it != groups_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

Event * DataStorage::get_event (id_type id)
{
    for (vector<Event *>::iterator it = events_vector_.begin (); it != events_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

Calendar * DataStorage::get_calendar (id_type id)
{
    for (vector<Calendar *>::iterator it = calendars_vector_.begin (); it != calendars_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

Queue * DataStorage::get_queue (id_type id)
{
    for (vector<Queue *>::iterator it = queues_vector_.begin (); it != queues_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

Event_Template * DataStorage::get_event_template (id_type id)
{
    for (vector<Event_Template *>::iterator it = event_templates_vector_.begin (); it != event_templates_vector_.end (); it++)
        if ((*it)->get_id () == id)
	    return *it;
    return NULL;
}

void DataStorage::delete_person (id_type id)
{
    for (vector<Person *>::iterator it = people_vector_.begin(); it != people_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            people_vector_.erase(it);
/*            remove_person(id);
*/            return;
        }
}

void DataStorage::delete_event (id_type id)
{
    for (vector<Event *>::iterator it = events_vector_.begin(); it != events_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            events_vector_.erase(it);
/*            remove_event(id);
*/            return;
        }
}

void DataStorage::delete_group (id_type id)
{
    for (vector<Group *>::iterator it = groups_vector_.begin(); it != groups_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            groups_vector_.erase(it);
/*            remove_group(id);
*/            return;
        }
}

void DataStorage::delete_queue (id_type id)
{
    for (vector<Queue *>::iterator it = queues_vector_.begin(); it != queues_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            queues_vector_.erase(it);
/*            remove_queue(id);
*/            return;
        }
}

void DataStorage::delete_calendar (id_type id)
{
    for (vector<Calendar *>::iterator it = calendars_vector_.begin(); it != calendars_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            calendars_vector_.erase(it);
            return;
        }
}

void DataStorage::delete_event_template (id_type id)
{
    for (vector<Event_Template *>::iterator it = event_templates_vector_.begin(); it != event_templates_vector_.end(); it ++)
        if ((*it)->get_id() == id)
        {
            delete *it;
            event_templates_vector_.erase(it);
/*            remove_event_template(id);
*/            return;
        }
}

void DataStorage::register_group (Group *group)
{
    if (groups_vector_.empty())
        group->set_id(0);
    else
        group->set_id (groups_vector_[groups_vector_.size () - 1]->get_id () + 1);
    groups_vector_.push_back (group);
/*    add_group (group->get_id ());
    set_group_attr (gaNAME, group->get_id(), group->get_name ());
    set_group_attr (gaDESCRIPTION, group->get_id(), group->get_description ());
    set_group_attr (gaCALENDAR, group->get_id(), itos (group->get_calendar ()->get_id ()));*/
}

void DataStorage::register_calendar (Calendar *calendar)
{
    if (calendars_vector_.empty())
        calendar->set_id(0);
    else
        calendar->set_id (calendars_vector_[calendars_vector_.size () - 1]->get_id () + 1);
    calendars_vector_.push_back (calendar);
}

void DataStorage::register_person (Person *person)
{
    if (people_vector_.empty())
        person->set_id(0);
    else
        person->set_id (people_vector_[people_vector_.size () - 1]->get_id () + 1);
    people_vector_.push_back (person);
 /*   add_person (person->get_id ());
    set_person_attr (paNAME, person->get_id (), person->get_name ());
    set_person_attr (paSURNAME, person->get_id (), person->get_surname ());
    set_person_attr (paBIRTHDAY, person->get_id (), itos(person->birthday ()));
    set_person_attr (paSEX, person->get_id (), (person->sex () == Person::MALE)?"MALE":"FEMALE");*/
}

void DataStorage::register_event (Event *event)
{
    if (events_vector_.empty())
        event->set_id(0);
    else
        event->set_id (events_vector_[events_vector_.size () - 1]->get_id () + 1);
    events_vector_.push_back (event);
/*    add_event (event->get_id ());
    set_event_attr (eaNAME, event->get_id (), event->get_name ());
    set_event_attr (eaGROUP, event->get_id (), itos(event->get_group ()->get_id ()));
    set_event_attr (eaBEGIN, event->get_id (), itos(event->get_begin ()));
    set_event_attr (eaEND, event->get_id (), itos(event->get_end ()));
    set_event_attr (eaDESCRIPTION, event->get_id (), event->get_description ());*/
}

void DataStorage::register_queue (Queue *queue)
{
    if (queues_vector_.empty())
        queue->set_id(0);
    else
        queue->set_id (queues_vector_[queues_vector_.size () - 1]->get_id () + 1);
    queues_vector_.push_back (queue);
/*    add_queue (queue->get_id ());
    set_queue_attr (qaNAME, queue->get_id (), queue->get_name());*/
}

void DataStorage::register_event_template (Event_Template *event_template)
{
    if (event_templates_vector_.empty())
        event_template->set_id(0);
    else
        event_template->set_id (event_templates_vector_[event_templates_vector_.size () - 1]->get_id () + 1);
    event_templates_vector_.push_back (event_template);
/*    add_event_template (event_template->get_id ());
    set_event_template_attr (taNAME, event_template->get_id (), event_template->get_name ());
    set_event_template_attr (taSCRIPT, event_template->get_id (), event_template->get_script ());*/
}

string DataStorage::get_person_attr(PersonAttribute attr, id_type id)
{
    return people_.get_cell_value(find_num_row(people_, id), attr);
}

void DataStorage::set_person_attr(PersonAttribute attr, id_type id, string value)
{
    people_.set_cell_value(find_num_row(people_, id), attr, value);
}

string DataStorage::get_group_attr(GroupAttribute attr, id_type id)
{
    return groups_.get_cell_value(find_num_row(groups_, id), attr);
}

void DataStorage::set_group_attr(GroupAttribute attr, id_type id, string value)
{
    groups_.set_cell_value(find_num_row(groups_, id), attr, value);
}

string DataStorage::get_event_attr(EventAttribute attr, id_type id)
{
    return events_.get_cell_value(find_num_row(events_, id), attr);
}

void DataStorage::set_event_attr(EventAttribute attr, id_type id, string value)
{
    events_.set_cell_value(find_num_row(events_, id), attr, value);
}

string DataStorage::get_queue_attr (QueueAttribute attr, id_type id)
{
    return queues_.get_cell_value (find_num_row(queues_, id), attr);
}

void DataStorage::set_queue_attr (QueueAttribute attr, id_type id, string value)
{
    queues_.set_cell_value (find_num_row(queues_, id), attr, value);
}

string DataStorage::get_event_template_attr (EventTemplateAttribute attr, id_type id)
{
    return event_templates_.get_cell_value (find_num_row(event_templates_, id), attr);
}

void DataStorage::set_event_template_attr (EventTemplateAttribute attr, id_type id, string value)
{
    event_templates_.set_cell_value (find_num_row (event_templates_, id), attr, value);
}

void DataStorage::add_person(id_type id)
{
    string flds[people_.get_rows_count()];
    flds[0] = itos(id);

    for(unsigned long long int i = 1; i < people_.get_rows_count(); i++)
        flds[i] = "";

    people_.add_row(flds);
}

void DataStorage::add_group(id_type id)
{
    string flds[groups_.get_rows_count()];
    flds[0] = itos(id);
    for(unsigned long long int i = 1; i < groups_.get_rows_count(); i++)
        flds[i] = "";

    groups_.add_row(flds);
}

void DataStorage::add_event(id_type id)
{
    string flds[events_.get_rows_count()];
    flds[0] = itos(id);

    for(unsigned long long int i = 1; i < events_.get_rows_count(); i++)
        flds[i] = "";

    events_.add_row(flds);
}

void DataStorage::add_queue (id_type id)
{
    string flds[queues_.get_rows_count()];
    flds[0] = itos(id);

    for (unsigned long long int i = 1; i < queues_.get_rows_count (); i++)
        flds[i] = "";

    queues_.add_row(flds);
}

void DataStorage::add_event_template (id_type id)
{
    string flds[event_templates_.get_rows_count()];
    flds[0] = itos(id);

    for (unsigned long long int i = 1; i < event_templates_.get_rows_count (); i++)
        flds[i] = "";
}

void DataStorage::remove_person(id_type id)
{
    people_.rem_row(find_num_row(people_, id));
}

void DataStorage::remove_group(id_type id)
{
    groups_.rem_row(find_num_row(groups_, id));
}

void DataStorage::remove_event(id_type id)
{
    events_.rem_row(find_num_row(events_, id));
}

void DataStorage::remove_queue(id_type id)
{
    queues_.rem_row(find_num_row(queues_, id));
}

void DataStorage::remove_event_template (id_type id)
{
    event_templates_.rem_row(find_num_row(queues_, id));
}

vector<id_type> DataStorage::get_person_ID_list()
{
    vector<id_type> ids;

    for(unsigned long long int i = 0; i < people_.get_rows_count(); i++)
    {
        ids.push_back(atoll(people_.get_cell_value(i, 0).c_str()));
    }

    return ids;
}

vector<id_type> DataStorage::get_event_ID_list()
{
    vector<id_type> ids;

    for(unsigned long long int i = 0; i < events_.get_rows_count(); i++)
    {
        ids.push_back(atoll(events_.get_cell_value(i, 0).c_str()));
    }

    return ids;
}

vector<id_type> DataStorage::get_group_ID_list()
{
    vector<id_type> ids;

    for(unsigned long long int  i = 0; i < groups_.get_rows_count(); i++)
    {
        ids.push_back(atoll(groups_.get_cell_value(i, 0).c_str()));
    }

    return ids;
}

vector<id_type> DataStorage::get_queue_ID_list()
{
    vector<id_type> ids;

    for(unsigned long long int i = 0; i < queues_.get_rows_count(); i++)
    {
        ids.push_back(atoll(queues_.get_cell_value(i, 0).c_str()));
    }

    return ids;
}

vector<id_type> DataStorage::get_event_template_ID_list()
{
    vector<id_type> ids;

    for(unsigned long long int i = 0; i < event_templates_.get_rows_count(); i++)
    {
        ids.push_back(atoll(event_templates_.get_cell_value(i, 0).c_str()));
    }

    return ids;
}

unsigned long long int DataStorage::get_calendar_bunches_count()
{
    return calendars_.get_rows_count();
}

CalendarBunch DataStorage::get_calendar_bunch(unsigned long long int num)
{
    CalendarBunch res;
    res.ID = atoll(calendars_.get_cell_value(num, 0).c_str());
    res.EventID = atoll(calendars_.get_cell_value(num, 1).c_str());
    return res;
}

void DataStorage::remove_calendar_bunch(unsigned long long int num)
{
    calendars_.rem_row(num);
}

void DataStorage::add_calendar_bunch(CalendarBunch bnch)
{
    string flds[2];
    flds[0] = itos(bnch.ID);
    flds[1] = itos(bnch.EventID);
    calendars_.add_row(flds);
}


unsigned long long int DataStorage::get_group_bunches_count ()
{
    return group_content_.get_rows_count();
}

GroupBunch DataStorage::get_group_bunch(unsigned long long int num)
{
    GroupBunch res;
    res.PersonID = atoll(group_content_.get_cell_value(num, 0).c_str());
    res.GroupID = atoll(group_content_.get_cell_value(num, 1).c_str());
    res.Status = group_content_.get_cell_value(num, 2);
    return res;
}

void DataStorage::remove_group_bunch(unsigned long long int num)
{
    group_content_.rem_row(num);
}

void DataStorage::add_group_bunch(GroupBunch bnch)
{
    string flds[3];
    flds[0] = itos(bnch.PersonID);
    flds[1] = itos(bnch.GroupID);
    flds[2] = bnch.Status;
    group_content_.add_row(flds);
}

unsigned long long int DataStorage::get_queue_bunches_count ()
{
    return queues_bunches_.get_rows_count();
}

QueueBunch DataStorage::get_queue_bunch(unsigned long long int num)
{
    QueueBunch res;
    res.QueueID = atoll(queues_bunches_.get_cell_value(num, 0).c_str());
    res.GroupID = atoll(queues_bunches_.get_cell_value(num, 1).c_str());
    return res;
}

void DataStorage::remove_queue_bunch (unsigned long long int num)
{
    queues_bunches_.rem_row(num);
}

void DataStorage::add_queue_bunch (QueueBunch bnch)
{
    string flds[2];
    flds [0] = itos (bnch.QueueID);
    flds [1] = itos (bnch.GroupID);
    queues_bunches_.add_row (flds);
}

