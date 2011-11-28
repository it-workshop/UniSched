
#pragma once

#include <string>
#include <vector>

#include "types.h"

using std::string;
using std::vector;

struct storage::dsrow_ {
    vector<string> fields;
};

class storage::TableDataStorage {
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

