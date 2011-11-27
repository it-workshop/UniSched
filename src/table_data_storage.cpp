#include <table_data_storage.h>

#include <stdio.h>

using namespace storage;

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
        error_ = LOAD_ERR;
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

