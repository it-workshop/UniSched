#include "storableobject.h"

using namespace Storage;

const int StorableObject::get_field_int (const std::string name) const
{
    return storage.get_field_int (id, name);
}

const std::string StorableObject::get_field_string (const std::string name) const
{
    return storage.get_field_string (id, name);
}

const time_t StorableObject::get_field_time (const std::string name) const
{
    return storage.get_field_time (id, name);
}

const StorableObject& StorableObject::get_field_object (const std::string name) const
{
    return storage.get_field_object (id, name);
}

void StorableObject::set_field(const std::string name, const int value)
{
    storage.set_field(id, name, value);
}

void StorableObject::set_field(const std::string name, const std::string value)
{
    storage.set_field(id, name, value);
}

void StorableObject::set_field(const std::string name, const time_t value)
{
    storage.set_field(id, name, value);
}
void StorableObject::set_field(const std::string name, const StorableObject& value)
{
    storage.set_field(id, name, value);
}

