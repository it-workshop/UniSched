#pragma once

#include <string>
#include <queue>
#include <vector>

#include "storage.h"

namespace Storage {

class AbstractStorage {
friend class StorableObject;
private:
protected:
    std::vector<StorableObject const *> objects_;
    
    virtual const int get_field_int(const int id, const std::string field) const = 0;
    virtual const std::string get_field_string(const int id, const std::string field) const = 0;
    virtual const time_t get_field_time(const int id, const std::string field) const = 0;
    virtual const std::string get_field_enum(const int id, const std::string field) const = 0;
    virtual const StorableObject& get_field_object(const int id, const std::string field) const = 0;
    virtual const std::vector<StorableObject const *> get_field_vector(const int id, const std::string field) const = 0;

    virtual void set_field(const int id, const std::string field, const int value) = 0;
    virtual void set_field(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const time_t value) = 0;
    virtual void set_field_enum(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const StorableObject& value) = 0;
    virtual void set_field_vector(const int id, const std::string field, const std::vector<StorableObject const *> vector) = 0;

    virtual void set_object(StorableObject const * object);

    virtual const int new_id();

public:
    struct Argument {
        const std::string field;
        enum {
            STRING,
            INTEGER,
            TIME,
            ENUMERATION
        } type;
        const std::string string;
        const int integer;
        const time_t time;
    };

    AbstractStorage() {}

    void remove(StorableObject const * object);

    template <class T>
    StorableObject const *create(std::vector<const Argument *>& parameters);

    virtual std::vector<StorableObject const *>& search(std::vector<Argument const *>& parameters) = 0;

    virtual StorableObject const * object(const int id) const { return objects_[id]; }
};

};

