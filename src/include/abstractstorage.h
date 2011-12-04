#pragma once

#include <string>
#include <queue>
#include <vector>

#include "storage.h"

namespace Storage {

class AbstractStorage {
friend class StorableObject;
private:
    std::vector<StorableObject> objects;
    std::queue<int> request_result;
protected:
    virtual const int get_field_int(const int id, const std::string field) const = 0;
    virtual const std::string get_field_string(const int id, const std::string field) const = 0;
    virtual const time_t get_field_time(const int id, const std::string field) const = 0;
    virtual const std::string get_field_enum(const int id, const std::string field) const = 0;
    virtual const StorableObject& get_field_object(const int id, const std::string field) const = 0;
    virtual std::vector<StorableObject const *> get_field_vector(const int id, const std::string field) const = 0;

    virtual void set_field(const int id, const std::string field, const int value) = 0;
    virtual void set_field(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const time_t value) = 0;
    virtual void set_field_enum(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const StorableObject& value) = 0;
    virtual void set_field_vector(const int id, const std::string field, const std::vector<StorableObject const *> vector) = 0;

public:
    AbstractStorage(): objects(), request_result() {}

    virtual const StorableObject& get_object(const int id) const { return objects[id]; }

    virtual const int search(const std::string field, const int value) const = 0;
    virtual const int search(const std::string field, const std::string value) const = 0;
    virtual const int search(const std::string field, const time_t value) const = 0;

    int get_next_result () { int id = request_result.front(); request_result.pop(); return id; }
    const bool is_next_result () const { return !request_result.empty (); }
};

};

