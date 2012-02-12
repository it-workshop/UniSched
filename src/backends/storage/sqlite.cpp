#include <manager.h>

class SQLiteStorage: public Storage::AbstractStorage {

protected:
    virtual const int
    get_field_int(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual const
    std::string get_field_string(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual const time_t
    get_field_time(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual const std::string
    get_field_enum(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual Storage::StorableObject *
    get_field_object(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual const std::vector<Storage::StorableObject *>
    get_field_vector(const int id, const std::string name) const
            throw (std::bad_cast);

    virtual void
    set_field(const int id, const std::string name, const int value)
            throw (std::bad_cast);

    virtual void
    set_field(const int id, const std::string name, const std::string value)
            throw (std::bad_cast);

    virtual void
    set_field(const int id, const std::string name, const time_t value)
            throw (std::bad_cast);

    virtual void
    set_field_enum(const int id, const std::string name,
        const std::string value)
            throw (std::bad_cast);

    virtual void
    set_field(const int id, const std::string name,
        Storage::StorableObject *value)
            throw (std::bad_cast);

    virtual void
    set_field_vector(const int id, const std::string name,
        const std::vector<Storage::StorableObject*> value)
            throw (std::bad_cast);
public:
    virtual void init(const std::vector<std::string>& args);

    virtual std::vector<Storage::StorableObject*>*
    search(std::vector<Storage::AbstractStorage::Argument*>& args);
};

void SQLiteStorage::init(const std::vector<std::string>& args)
{
    //TODO: empty method :(
}

const int
SQLiteStorage::get_field_int(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

const std::string
SQLiteStorage::get_field_string(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

const time_t
SQLiteStorage::get_field_time(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

const std::string
SQLiteStorage::get_field_enum(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

Storage::StorableObject *
SQLiteStorage::get_field_object(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

const std::vector<Storage::StorableObject *>
SQLiteStorage::get_field_vector(const int id, const std::string name) const
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field(const int id, const std::string name, const int value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field(const int id, const std::string name,
    const std::string value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field(const int id, const std::string name,
    const time_t value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field_enum(const int id, const std::string name,
    const std::string value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field(const int id, const std::string name,
    Storage::StorableObject *value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

void
SQLiteStorage::set_field_vector(const int id, const std::string name,
    const std::vector<Storage::StorableObject*> value)
        throw (std::bad_cast)
{
    //TODO: empty method :(
}

std::vector<Storage::StorableObject*>*
SQLiteStorage::search(std::vector<Storage::AbstractStorage::Argument*>& args)
{
    //TODO: empty method :(
}

SQLiteStorage _object;

