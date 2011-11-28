
#pragma once

#include "types.h"
#include "table_data_storage.h"
#include "data_storage.h"

class storage::FileStorage : public storage::DataStorage {
public:
     FileStorage ();
    ~FileStorage ();
    void setup(string location, string user, string password, string bdname);
    bool load();
    bool save();
private:
    string path_;
};

