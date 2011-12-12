#pragma once

#include <string>
#include <vector>

namespace Storage {

class StorableObject {
friend class AbstractStorage;
private:
    const int id_;
    class AbstractStorage& storage_;

protected:
    const int id() const { return id_; };

    const int get_field_int(const std::string name) const;
    const std::string get_field_string(const std::string name) const;
    const time_t get_field_time(const std::string name) const;
    const std::string get_field_enum(const std::string name) const;
    const StorableObject * get_field_object(const std::string name) const;
    std::vector<StorableObject *> get_field_vector(const std::string name) const;

    void set_field(const std::string name, const int value);
    void set_field(const std::string name, const std::string value);
    void set_field(const std::string name, const time_t value);
    void set_field_enum(const std::string name, const std::string);
    void set_field(const std::string name, StorableObject * value);
    void set_field_vector(const std::string name, const std::vector<StorableObject *>& vector);

    virtual void save() = 0;
    virtual void load() = 0;

public:

    StorableObject(const int id, AbstractStorage& storage): id_(id), storage_(storage) {}
};

};

#include <abstractstorage.h>
