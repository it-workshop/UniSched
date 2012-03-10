#include <abstractui.h>

#include <sqlite3.h>

class SQLiteStorage: public Core::AbstractStorage {
friend SQLiteStorage_read_callback();
private:
    std::string db_name_;
    bool create;
    sqlite3 connection_;
    objid_t current_id_;
    std::string field_name_;
    std::string string_value_;
    std::string name_;
    time_t time_value_;

    enum {
        READ_OBJECTS,
        READ_FIELDS,
        READ_STRING,
        READ_TIME,
        READ_CONNECTIONS,
        CHECK_STRING,
        CHECK_TIME,
        CHECK_OTHER
    } read_state_;

    void check_create();
    void load();
public:
    SQLiteStorage(std::vector<Core::Module *>* modules, void *handle):
            AbstractStorage("SQLITE", modules, handle),
            db_name_(".raspisator.db"), create_(false)
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
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == "--sqlite-db")
        {
            db_name_ = *++it;
        }

        if (*it == "--sqlite-create")
        {
            create_ = true;
        }
    }
}

void SQLiteStorage::push(const Core::objid_t id, const std::string& name,
        const boost::any& value)
{
    if (typeid(std::string) == value.type())
    {
        read_state_ = CHECK_STRING;
        sqlite3_exec(connection_,
            "SELECT * FROM fields WHERE object=" + id + " AND name=" + name +
                ";", SQLiteStorage_read_callback, this, nullptr);
        return;
    }
    if (typeid(std::string) == value.type())
    {
        read_state_ = CHECK_TIME;
        sqlite3_exec(connection_,
            "SELECT * FROM fields WHERE object=" + id + " AND name=" + name +
                ";", SQLiteStorage_read_callback, this, nullptr);
        return;
    }
    throw boost::bad_any_cast();
}

void SQLiteStorage::connect()
{
    sqlite3_open(db_name_, &connection_);

    if (SQLITE_OK != sqlite3_errcode(db))
    {
        throw db;
    }

    if (create_)
    {
        create();
    }

    load()
}

void SQLiteStorage::create()
{
    sqlite3_exec( connection_,
        "DROP TABLE IF EXISTS objects;"\
        "CREATE TABLE objects (id INT PRIMARY KEY, type INT);"\
        "DROP TABLE IF EXISTS fields;"\
        "CREATE TABLE fields (object INT, name VARCHAR(32), type INT, value INT);"\
        "DROP TABLE IF EXISTS strings;"\
        "CREATE TABLE strings (id INT PRIMARY KEY, value TEXT);"\
        "DROP TABLE IF EXISTS timestamps;"\
        "CREATE TABLE timestamps (id INT PRIMARY KEY, value TIMESTAMP);"\
        "DROP TABLE IF EXISTS connections;"\
        "CREATE TABLE connections (id INT, with INT);",
        nullptr, nullptr, nullptr);
}

void SQLiteStorage::load()
{
    read_state_ = READ_OBJECTS;
    sqlite3_exec(connection_, "SELECT * FROM objects;",
        SQLiteStorage_read_callback, this, nullptr);
    read_state_ = READ_FIELDS;
    sqlite3_exec(connection_, "SELECT * FROM fields;",
        SQLiteStorage_read_callback, this, nullptr);
    read_state_ = READ_CONNECTIONS;
    sqlite3_exec(connection_, "SELECT * FROM connectios;",
        SQLiteStorage_read_callback, this, nullptr);
}

void SQLiteStorage::disconnect()
{
    sqlite3_close(connection_);
}

void SQLiteStorage::create(const Core::Object *object)
{
    sqlite3_exec(connection_, "INSERT INTO objects (type) VALUES (" +
        object->type() + ");", nullptr, nullptr, nullptr);
}

void SQLiteStorage::remove(const Core::objid_t id)
{
    sqlite3_exec(connection_, "DELETE FROM fields WHERE object=" + id + ");"\
        "DELETE FROM objects WHERE id=" + id + ");", nullptr, nullptr, nullptr);
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new SQLiteStorage(modules, handle);
}

};

