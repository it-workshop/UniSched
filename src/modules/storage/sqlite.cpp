#include <iostream>

#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

#include <sqlite3.h>

#include <boost/format.hpp>

class SQLiteStorage: public Core::AbstractStorage {
friend int SQLiteStorage_load_type(void *self_, int fields_count,
        char **values, char **fields);
friend int SQLiteStorage_load_time(void *self_, int fields_count,
        char **values, char **fields);
friend int SQLiteStorage_load_string(void *self_, int fields_count,
        char **values, char **fields);
friend int SQLiteStorage_load_connections(void *self_, int fields_count,
        char **values, char **fields);
friend int SQLiteStorage_load_id(void *self_, int fields_count,
        char **values, char **fields);
private:
    std::string db_name_;
    bool create_;
    sqlite3 *connection_;
    bool loading_;

    void create_tables();
    void load();
public:
    SQLiteStorage(std::vector<Core::Module *>* modules, void *handle);

    virtual void init(const std::vector<std::string>& args);
    virtual void push(const Core::objid_t id, const std::string& name,
            const boost::any& value);
    virtual void push_connect(Core::objid_t id, Core::objid_t with,
            bool connect);
    virtual void connect();
    virtual void disconnect();
    virtual void create(const Core::Object *object);
    virtual void remove(const Core::objid_t id);
};

SQLiteStorage::SQLiteStorage(std::vector<Core::Module *>* modules,
        void *handle):
    AbstractStorage("SQLITE", modules, handle),
    db_name_(".raspisator.db"), create_(false)
{}

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

static int SQLiteStorage_push_select(void *found, int, char **, char **)
{
    *((bool *)found) = true;
}

void SQLiteStorage::push(const Core::objid_t id, const std::string& name,
        const boost::any& value)
{
    if (loading_)
    {
        return;
    }
    std::string query;
    bool found = false;
    char *error = nullptr;
    query = str(boost::format ("SELECT * FROM %s WHERE object=%u AND name='%s';") %
        (typeid(const time_t) == value.type() ? "times" : "strings") % id % name);
    if (sqlite3_exec(connection_, query.c_str(),
        SQLiteStorage_push_select, &found, &error))
    {
        std::cerr << "SQLITE: push: " << error << std::endl;
        sqlite3_free(error);
        return;
    }

    query = str(boost::format ("%s %s %s %s %s%s%u%s%s") %
        (found ? "UPDATE " : "INSERT INTO ") %
        (typeid(const time_t) == value.type() ? "times" : "strings") %
        (found ? " SET value=" : "(value, object, name) VALUES(") %
        (typeid(const time_t) == value.type() ?
            boost::str(boost::format ("%s") % boost::any_cast<const time_t>(value)) :
            boost::str(boost::format ("'%s'") % boost::any_cast<const std::string&>(value))) %
        (found ? " WHERE object=" : ", ") % id %
        (found ? " AND name='" : ", '") % name %
        (found ? "';" : "');"));
    if (sqlite3_exec(connection_, query.c_str(), nullptr, nullptr,
        &error))
    {
        std::cerr << "SQLITE: push: " << error << std::endl;
        sqlite3_free(error);
    }
}

void SQLiteStorage::push_connect(const Core::objid_t id,
    const Core::objid_t with, bool connect)
{
    if (loading_)
    {
        return;
    }
    std::string query;
    char *error = nullptr;
    query  = boost::str(boost::format("%s connections %s%u%s%u%s") %
        (connect ? "INSERT INTO" : "DELETE FROM") %
        (connect ? "(object, with) VALUES(" : " WHERE object=") % id %
        (connect ? ", " : " AND with=") % with % (connect ? ");" : ";"));
    if (sqlite3_exec(connection_, query.c_str(), nullptr, nullptr, &error))
    {
        std::cerr << "SQLITE: push_connect: " << error << std::endl;
        sqlite3_free(error);
        return;
    }
}


void SQLiteStorage::connect()
{
    if (SQLITE_OK != sqlite3_open(db_name_.c_str(), &connection_))
    {
        throw sqlite3_errcode(connection_);
    }
    if (create_)
    {
        create_tables();
        return;
    }
    load();
}

void SQLiteStorage::create_tables()
{
    char *error = nullptr;
    if (sqlite3_exec( connection_,
        "DROP TABLE IF EXISTS objects;"\
        "CREATE TABLE objects (id INT, type INT);"\
        "DROP TABLE IF EXISTS times;"\
        "CREATE TABLE times (object INT, name VARCHAR(32), value INT);"\
        "DROP TABLE IF EXISTS strings;"\
        "CREATE TABLE strings (object INT, name VARCHAR(32), value TEXT);"\
        "DROP TABLE IF EXISTS connections;"\
        "CREATE TABLE connections (object INT, with INT);",
         nullptr, nullptr, &error))
    {
        std::cerr << "SQLITE: create_tables: " << error << std::endl;
        sqlite3_free(error);
    }
}
 
int SQLiteStorage_load_type(void *self_, int fields_count, char **values,
        char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 2)
    {
        std::cerr << "SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    Core::obj_t type;
    for (int i = 0; i < 2; i++)
    {
        if ("id" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> id;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: id is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if ("type" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> (int&)type;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: type is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        std::cerr << "SQLITE: load: unknown field! " << fields[i]
            << std::endl;
        return -1;
    }
    switch(type)
    {
    case Core::PERSON:
        self->create_in_memory<Core::Person>(id);
        break;
    case Core::GROUP:
        self->create_in_memory<Core::Group>(id);
        break;
    case Core::EVENT:
        self->create_in_memory<Core::Event>(id);
        break;
    default:
        std::cerr << "SQLITE: load: invalid object's type!"
            << std::endl;
        return -1;
    }
    return 0;
}

int SQLiteStorage_load_time(void *self_, int fields_count, char **values,
        char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 3)
    {
        std::cerr << "SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    time_t value;
    std::string name;
    for (int i = 0; i < 3; i++)
    {
        if ("object" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> id;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if ("value" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> value;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: value is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if ("name" == std::string(fields[i]))
        {
            name = values[i];
            continue;
        }
        std::cerr << "SQLITE: load: unknown field!" << fields[i] << std::endl;
        return -1;
    }
    self->objects()[id]->update(name, value);
    return 0;
}

int SQLiteStorage_load_string(void *self_, int fields_count, char **values,
        char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 3)
    {
        std::cerr << "SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    std::string name;
    std::string value;
    for (int i = 0; i < 3; i++)
    {
        if ("object" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> id;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if ("name" == std::string(fields[i]))
        {
            name = values[i];
            continue;
        }
        if ("value" == std::string(fields[i]))
        {
            value = values[i];
            continue;
        }
        std::cerr << "SQLITE: load: unknown field! " << fields[i]
            << std::endl;
        return -1;
    }
    self->objects()[id]->update(name, value);
    return 0;
}

int SQLiteStorage_load_connections(void *self_, int fields_count,
        char **values, char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 2)
    {
        std::cerr<< "SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    Core::objid_t with;
    for (int i = 0; i < 2; i++)
    {
        if ("object" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> id;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if ("with" == std::string(fields[i]))
        {
            std::stringstream stream;
            stream << values[i];
            stream >> with;
            if (stream.fail())
            {
                std::cerr << "SQLITE: load: with is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        std::cerr << "SQLITE: load: unknown field: " << fields[i]
            << std::endl;
        return -1;
    }
    self->objects()[id]->connect(self->objects()[with]);
    return 0;
}

int SQLiteStorage_load_id(void *self_, int fields_count, char **values,
        char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 1)
    {
        std::cerr << "SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    if ("max(id)" != std::string(*fields))
    {
        std::cerr << "SQLITE: load: unknown field: " << *fields << std::endl;
        return -1;
    }
    std::stringstream stream;
    stream << *values;
    Core::objid_t id;
    stream >> id;
    if (stream.fail())
    {
        self->set_new_id(0);
        return 0;
    }
    self->set_new_id(id + 1);
    return 0;
}

void SQLiteStorage::load()
{
    loading_ = true;
    char *error = nullptr;
    if (sqlite3_exec (connection_, "SELECT id, type FROM objects;",
            SQLiteStorage_load_type, this, &error)
    || sqlite3_exec(connection_,
        "SELECT object, name, value FROM times;", SQLiteStorage_load_time, 
        this, &error)
    || sqlite3_exec(connection_, "SELECT object, name, value FROM strings;",
        SQLiteStorage_load_string, this, &error)
    || sqlite3_exec(connection_, "SELECT object, with FROM connections;",
        SQLiteStorage_load_connections, this, &error)
    || sqlite3_exec(connection_, "SELECT max(id) FROM (SELECT id FROM objects);",
        SQLiteStorage_load_id, this, &error))
    {
        std::cerr << "SQLITE: load: " << error << std::endl;
        sqlite3_free(error);
        return;
    }
    loading_ = false;
}

void SQLiteStorage::disconnect()
{
    sqlite3_close(connection_);
}

void SQLiteStorage::create(const Core::Object *object)
{
    if (loading_)
    {
        return;
    }
    char *error = nullptr;
    std::stringstream query;
    query << "INSERT INTO objects (id, type) VALUES(" << object_id(object)
        << ", " << int(object->type())<< ")";
    if (sqlite3_exec(connection_, query.str().c_str(), nullptr, nullptr, &error))
    {
        std::cerr << "SQLITE: create: " << error << std::endl;
        sqlite3_free(error);
        return;
    }
}

void SQLiteStorage::remove(const Core::objid_t id)
{
    char *error = nullptr;
    std::stringstream query;
    query << "DELETE FROM objects WHERE id = " << id;
    if (sqlite3_exec(connection_, query.str().c_str(), nullptr, nullptr, &error))
    {
        std::cerr << "SQLITE: remove: " << error << std::endl;
        sqlite3_free(error);
        return;
    }
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new SQLiteStorage(modules, handle);
}

};

