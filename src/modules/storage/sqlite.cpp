#include <sstream>
#include <iostream>

#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

#include <sqlite3.h>

#include <utils.h>

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
    std::wstring db_name_;
    bool create_;
    sqlite3 *connection_;
    bool loading_;

    void create_tables();
    void load();
public:
    SQLiteStorage(std::vector<Core::Module *>* modules, void *handle);

    virtual void init(const std::vector<std::wstring>& args);
    virtual void push(const Core::objid_t id, const std::wstring& name,
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
    AbstractStorage(L"SQLITE", modules, handle),
    db_name_(L".raspisator.db"), create_(false)
{}

void SQLiteStorage::init(const std::vector<std::wstring>& args)
{
    init_iconv("UTF8");
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == L"--sqlite-db")
        {
            db_name_ = *++it;
        }

        if (*it == L"--sqlite-create")
        {
            create_ = true;
        }
    }
}

static int SQLiteStorage_push_select(void *found, int, char **, char **)
{
    *((bool *)found) = true;
}

void SQLiteStorage::push(const Core::objid_t id, const std::wstring& name,
        const boost::any& value)
{
    if (loading_)
    {
        return;
    }
    std::wstringstream query;
    bool found = false;
    char *error = nullptr;
    query << L"SELECT * FROM ";
    if (typeid(const time_t) == value.type())
    {
        query << L"times";
    }
    else
    {
        query << L"strings";
    }
    query << L" WHERE object=" << id << L" AND name='" << name << "';";
    if (sqlite3_exec(connection_, iconv(query.str()),
        SQLiteStorage_push_select, &found, &error))
    {
        std::wcerr << L"SQLITE: push: " << utils::iconv(error) << std::endl;
        sqlite3_free(error);
        return;
    }

    query << (found ? L"UPDATE " : L"INSERT INTO ");
    if (typeid(const time_t) == value.type())
    {
        query << L"times" << (found ? L" SET value=" : L"(value, object, name) VALUES(")
            << boost::any_cast<const time_t>(value);
    }
    else
    {
        query << L"strings"
            << (found ? L" SET value='" : L"(value, object, name) VALUES('")
            << boost::any_cast<const std::wstring&>(value) << L'\'';
    }
    query << (found ? L" WHERE object=" : L", ") << id
        << (found ? L" AND name='" : L", '") << name << (found ? L"';" : L"');");
    if (sqlite3_exec(connection_, iconv(query.str()), nullptr, nullptr,
        &error))
    {
        std::wcerr << L"SQLITE: push: " << utils::iconv(error) << std::endl;
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
    std::wstringstream query;
    char *error = nullptr;
    query << (connect ? L"INSERT INTO" : L"DELETE FROM");
    query << L" connections"
        << (connect ? L"(object, with) VALUES(" : L" WHERE object=") << id
        << (connect ? L", " : L" AND with=") << with << (connect ? L");" : L";");
    if (sqlite3_exec(connection_, iconv(query.str()), nullptr, nullptr, &error))
    {
        std::wcerr << L"SQLITE: push_connect: " << utils::iconv(error) << std::endl;
        sqlite3_free(error);
        return;
    }
}


void SQLiteStorage::connect()
{
    if (SQLITE_OK != sqlite3_open(utils::iconv(db_name_), &connection_))
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
        std::wcerr << L"SQLITE: create_tables: " << utils::iconv(error) << std::endl;
        sqlite3_free(error);
    }
}
 
int SQLiteStorage_load_type(void *self_, int fields_count, char **values,
        char **fields)
{
    SQLiteStorage *self = reinterpret_cast<SQLiteStorage *>(self_);
    if (fields_count != 2)
    {
        std::wcerr << L"SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    Core::obj_t type;
    for (int i = 0; i < 2; i++)
    {
        if (L"id" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << values[i];
            stream >> id;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: id is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if (L"type" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << values[i];
            stream >> (int&)type;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: type is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        std::wcerr << L"SQLITE: load: unknown field! " << utils::iconv(fields[i])
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
        std::wcerr << L"SQLITE: load: invalid object's type!"
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
        std::wcerr << L"SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    time_t value;
    std::wstring name;
    for (int i = 0; i < 3; i++)
    {
        if (L"object" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << utils::iconv(values[i]);
            stream >> id;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if (L"value" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << utils::iconv(values[i]);
            stream >> value;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: value is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if (L"name" == std::wstring(utils::iconv(fields[i])))
        {
            name = utils::iconv(values[i]);
            continue;
        }
        std::wcerr << L"SQLITE: load: unknown field!" << utils::iconv(fields[i]) << std::endl;
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
        std::wcerr << L"SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    std::wstring name;
    std::wstring value;
    for (int i = 0; i < 3; i++)
    {
        if (L"object" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << utils::iconv(values[i]);
            stream >> id;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if (L"name" == std::wstring(utils::iconv(fields[i])))
        {
            name = utils::iconv(values[i]);
            continue;
        }
        if (L"value" == std::wstring(utils::iconv(fields[i])))
        {
            value = utils::iconv(values[i]);
            continue;
        }
        std::wcerr << L"SQLITE: load: unknown field! " << utils::iconv(fields[i])
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
        std::wcerr<< L"SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    Core::objid_t id;
    Core::objid_t with;
    for (int i = 0; i < 2; i++)
    {
        if (L"object" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << utils::iconv(values[i]);
            stream >> id;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: object is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        if (L"with" == std::wstring(utils::iconv(fields[i])))
        {
            std::wstringstream stream;
            stream << utils::iconv(values[i]);
            stream >> with;
            if (stream.fail())
            {
                std::wcerr << L"SQLITE: load: with is not integer!"
                    << std::endl;
                return -1;
            }
            continue;
        }
        std::wcerr << L"SQLITE: load: unknown field: " << utils::iconv(fields[i])
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
        std::wcerr << L"SQLITE: load: invalid fields count!" << std::endl;
        return -1;
    }
    if (L"max(id)" != std::wstring(utils::iconv(*fields)))
    {
        std::wcerr << L"SQLITE: load: unknown field: " << utils::iconv(*fields) << std::endl;
        return -1;
    }
    std::wstringstream stream;
    stream << utils::iconv(*values);
    Core::objid_t id;
    stream >> id;
    if (stream.fail())
    {
        std::wcerr << L"SQLITE: load: id is not integer!" << std::endl;
        return -1;
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
        std::wcerr << L"SQLITE: load: " << utils::iconv(error) << std::endl;
        sqlite3_free(error);
        return;
    }
    loading_ = false;
}

void SQLiteStorage::disconnect()
{
    sqlite3_close(connection_);
    deinit_iconv();
}

void SQLiteStorage::create(const Core::Object *object)
{
    if (loading_)
    {
        return;
    }
    char *error = nullptr;
    std::wstringstream query;
    query << L"INSERT INTO objects (id, type) VALUES(" << object_id(object)
        << L", " << int(object->type())<< L")";
    if (sqlite3_exec(connection_, iconv(query.str()), nullptr, nullptr, &error))
    {
        std::wcerr << L"SQLITE: create: " << utils::iconv(error) << std::endl;
        sqlite3_free(error);
        return;
    }
}

void SQLiteStorage::remove(const Core::objid_t id)
{
    char *error = nullptr;
    std::wstringstream query;
    query << L"DELETE FROM objects WHERE id = " << id;
    if (sqlite3_exec(connection_, iconv(query.str()), nullptr, nullptr, &error))
    {
        std::wcerr << L"SQLITE: remove: " << utils::iconv(error) << std::endl;
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

