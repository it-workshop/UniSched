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

bool stob(string str)
{
    return (str == "true" || str == "TRUE");
}

TableDataStorage::TableDataStorage()
{
    fields_count_ = 0;
    rows_count_ = 0;
    error_ = NO_ERR;
}

TableDataStorage::~TableDataStorage()
{
}

Errors TableDataStorage::get_last_error()
{
    return error_;
}

void TableDataStorage::create_table(int fields_count)
{
    fields_count_ = fields_count;
    vector<dsrow> tempr;
    rows_ = tempr;
}

void TableDataStorage::add_row(string fields[])
{
    dsrow nrow;

    for(int i = 0; i < fields_count_; i++)
    {
        nrow.fields.push_back(fields[i]);
    }

    rows_.push_back(nrow);
    rows_count_++;
}

string TableDataStorage::get_cell_value(int row, int field)
{
    if(row >= rows_count_ || field >= fields_count_)
    {
        error_ = GET_CELL_VALUE_ERR;
	return NULL;
    }

    return rows_[row].fields[field];
}

bool TableDataStorage::set_cell_value(int row, int field, string value)
{
    if(row >= rows_count_ || field >= fields_count_)
    {
        error_ = SET_CELL_VALUE_ERR;
        return false;
    }
    
    rows_[row].fields[field] = value;
    return true;
}

bool TableDataStorage::load_table(string filename)
{
    FILE * lt = fopen(filename.c_str (), "r");

    if(!lt)
    {
        error_ = SAVE_ERR;
        return false;
    }

    dsrow * rw = new dsrow();

    string str;
    string tsym = " ";

    while(true)
    {
        tsym[0] = fgetc(lt);

        if(tsym[0] == EOF)
	    break;
	
	if(tsym[0] == ';' || tsym[0] == ',')
	{
            rw->fields.push_back(str);
            str="";
            tsym[0] = fgetc(lt);
	}

	if(tsym[0] == '\n')
	{
	    rw->fields.push_back(str);
            str="";
	    rows_.push_back(*rw);
            rw = new dsrow();
            tsym[0] = fgetc(lt);
        }
	    if(tsym[0]!='\"')
            str.append(tsym);
	}
    
    fields_count_ = rows_[0].fields.size();
    rows_count_ = rows_.size();

    return true;
}

bool TableDataStorage::save_table(string filename)
{
    FILE * lt = fopen(filename.c_str(), "w");
    string str="";

    for(int i = 0; i < rows_count_; i++)
    {
        for(int d = 0; d < fields_count_; d++)
	{
            str = rows_[i].fields[d];
            fputs(str.c_str(), lt);

            if(d < fields_count_ - 1)
	        fputc(';', lt);
        }

        fputc('\n', lt);
    }

    return true;
}

void TableDataStorage::rem_row(int row)
{
    for (vector<dsrow>::iterator it = rows_.begin(); it != rows_.end (); it++, row--)
    {
        if (!row)
	    it = rows_.erase (it);
    }

    rows_count_--;
}

unsigned long long int TableDataStorage::get_rows_count()
{
    return rows_count_;
}

unsigned long long int TableDataStorage::get_fields_count()
{
    return fields_count_;
}

void FileStorage::setup(string location, string, string, string)
{
    path_ = location;
}

void FileStorage::setup(string location)
{
    setup (location);
}

bool FileStorage::load()
{
    string pth = path_;

    if (!people_.load_table(pth.append("people.csv")))
        return false;
    pth = path_;

    if (!groups_.load_table(pth.append("groups.csv")))
        return false;
    pth = path_;

    if (!events_.load_table(pth.append("events.csv")))
        return false;
    pth = path_;

    if (!group_content_.load_table(pth.append("group_content.csv")))
        return false;
    pth = path_;

    if (!calendars_.load_table(pth.append("calendars.csv")))
        return false;

    return true;
}

bool FileStorage::save()
{
    string pth = path_;

    people_.save_table(pth.append("people.csv"));
    pth = path_;

    groups_.save_table(pth.append("groups.csv"));
    pth = path_;

    events_.save_table(pth.append("events.csv"));
    pth = path_;

    group_content_.save_table(pth.append("group_content.csv"));
    pth = path_;

    calendars_.save_table(pth.append("calendars.csv"));
    pth = path_;

    return true;
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

