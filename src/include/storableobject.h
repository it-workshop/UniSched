#pragma once

#include "abstractstorage.h"

namespace Storage {

class StorableObject {
private:
    const int id;
    class AbstractStorage& storage;

protected:
    const int get_id() { return id; }

    const int get_field_int(const std::string name) const;
    const std::string get_field_string(const std::string name) const;
    const time_t get_field_time(const std::string name) const;
    const std::string get_field_enum(const std::string name) const;
    const StorableObject& get_field_object(const std::string name) const;
    std::vector<StorableObject const *> get_field_vector(const std::string name) const;

    void set_field(const std::string name, const int value);
    void set_field(const std::string name, const std::string value);
    void set_field(const std::string name, const time_t value);
    void set_field_enum(const std::string name, const std::string);
    void set_field(const std::string name, const StorableObject& value);
    void set_field_vector(const std::string name, const std::vector<StorableObject const *>& vector);

    virtual void save() = 0;
    virtual void load() = 0;

public:

    StorableObject(const int id, AbstractStorage& storage): id(id), storage(storage) {}
};

};

