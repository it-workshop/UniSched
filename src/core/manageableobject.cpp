#include <manageableobject.h>

using namespace Core;

const int ManageableObject::get_field_int(const std::string name) const
{
    return manager_.get_field_int(id_, name);
}

const std::string ManageableObject::get_field_string(const std::string name) const
{
    return manager_.get_field_string(id_, name);
}

const time_t ManageableObject::get_field_time(const std::string name) const
{
    return manager_.get_field_time(id_, name);
}

const std::string ManageableObject::get_field_enum (const std::string name) const
{
    return manager_.get_field_enum(id_, name);
}

const ManageableObject * ManageableObject::get_field_object (const std::string name) const
{
    return manager_.get_field_object (id_, name);
}

std::vector<ManageableObject *> ManageableObject::get_field_vector(const std::string name) const
{
    return manager_.get_field_vector(id_, name);
}

void ManageableObject::set_field(const std::string name, const int value)
{
    manager_.set_field(id_, name, value);
}

void ManageableObject::set_field(const std::string name, const std::string value)
{
    manager_.set_field(id_, name, value);
}

void ManageableObject::set_field(const std::string name, const time_t value)
{
    manager_.set_field(id_, name, value);
}

void ManageableObject::set_field_enum(const std::string name, const std::string value)
{
    manager_.set_field_enum(id_, name, value);
}

void ManageableObject::set_field(const std::string name, ManageableObject * value)
{
    manager_.set_field(id_, name, value);
}

void ManageableObject::set_field_vector(const std::string name, const std::vector<ManageableObject *>& vector)
{
    manager_.set_field_vector(id_, name, vector);
}

