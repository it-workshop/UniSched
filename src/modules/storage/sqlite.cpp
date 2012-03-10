#include <abstractui.h>

class SQLiteStorage: public Core::AbstractStorage {

public:
    SQLiteStorage(std::vector<Core::Module *>* modules, void *handle):
            AbstractStorage("SQLITE", modules, handle)
    {}

    virtual void init(const std::vector<std::string>& args);
    virtual void push(const Core::objid_t id, const std::string& name,
            const boost::any& value);
    virtual void connect();
    virtual void disconnect();
    virtual void create(const Core::Object *object);
    virtual void remove(const Core::objid_t id);
};

void SQLiteStorage::init(const std::vector<std::string>& args)
{
}

void SQLiteStorage::push(const Core::objid_t id, const std::string& name,
        const boost::any& value)
{
}

void SQLiteStorage::connect()
{
}

void SQLiteStorage::disconnect()
{
}

void SQLiteStorage::create(const Core::Object *object)
{
}

void SQLiteStorage::remove(const Core::objid_t id)
{
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new SQLiteStorage(modules, handle);
}

};

