#include <abstractui.h>

class SQLiteStorage: public Core::AbstractStorage {

public:
    SQLiteStorage(std::vector<Core::Module *>* modules, void *handle):
            AbstractStorage("SQLITE", modules, handle)
    {}

    virtual void init(const std::vector<std::string>& args);
    virtual void push(const std::string& name, const boost::any& value);
    virtual void load();
    virtual void save();
};

void SQLiteStorage::init(const std::vector<std::string>& args)
{
}

void SQLiteStorage::push(const std::string& name, const boost::any& value)
{
}

void SQLiteStorage::load()
{
}

void SQLiteStorage::save()
{
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new SQLiteStorage(modules, handle);
}

};

