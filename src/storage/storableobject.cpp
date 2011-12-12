#include <storableobject.h>

using namespace Storage;

const int StorableObject::get_field_int(const std::string name) const
{
    return storage_.get_field_int(id_, name);
}

const std::string StorableObject::get_field_string(const std::string name) const
{
    return storage_.get_field_string(id_, name);
}

const time_t StorableObject::get_field_time(const std::string name) const
{
    return storage_.get_field_time(id_, name);
}

const std::string StorableObject::get_field_enum (const std::string name) const
{
    return storage_.get_field_enum(id_, name);
}

const StorableObject * StorableObject::get_field_object (const std::string name) const
{
    return storage_.get_field_object (id_, name);
}

std::vector<StorableObject *> StorableObject::get_field_vector(const std::string name) const
{
    return storage_.get_field_vector(id_, name);
}

void StorableObject::set_field(const std::string name, const int value)
{
    storage_.set_field(id_, name, value);
}

void StorableObject::set_field(const std::string name, const std::string value)
{
    storage_.set_field(id_, name, value);
}

void StorableObject::set_field(const std::string name, const time_t value)
{
    storage_.set_field(id_, name, value);
}

void StorableObject::set_field_enum(const std::string name, const std::string value)
{
    storage_.set_field_enum(id_, name, value);
}

void StorableObject::set_field(const std::string name, StorableObject * value)
{
    storage_.set_field(id_, name, value);
}

void StorableObject::set_field_vector(const std::string name, const std::vector<StorableObject *>& vector)
{
    storage_.set_field_vector(id_, name, vector);
}

