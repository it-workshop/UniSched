#pragma once

#include <string>
#include <vector>

#include <storableobject.h>

namespace Storage {

class AbstractStorage {
friend class StorableObject;
private:
protected:
    std::vector<StorableObject *> objects_;
    
    virtual const int get_field_int(const int id, const std::string field) const = 0;
    virtual const std::string get_field_string(const int id, const std::string field) const = 0;
    virtual const time_t get_field_time(const int id, const std::string field) const = 0;
    virtual const std::string get_field_enum(const int id, const std::string field) const = 0;
    virtual const StorableObject& get_field_object(const int id, const std::string field) const = 0;
    virtual const std::vector<StorableObject *> get_field_vector(const int id, const std::string field) const = 0;

    virtual void set_field(const int id, const std::string field, const int value) = 0;
    virtual void set_field(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const time_t value) = 0;
    virtual void set_field_enum(const int id, const std::string field, const std::string value) = 0;
    virtual void set_field(const int id, const std::string field, const StorableObject& value) = 0;
    virtual void set_field_vector(const int id, const std::string field, const std::vector<StorableObject *> vector) = 0;

    virtual void set_object(StorableObject * object);

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

    void remove(StorableObject * object);

    template <class T>
    StorableObject * create(std::vector<const Argument *>& parameters)
    {
        T * object = new T(new_id(), *this);
    
        set_object(dynamic_cast<StorableObject *>(object));

        for (auto it = parameters.begin(); it != parameters.end(); it++)
        {
            switch ((*it)->type)
            {
            case Argument::STRING:
                set_field((dynamic_cast<StorableObject *>(object))->id(),
                        (*it)->field, (*it)->string);
                break;
            case Argument::INTEGER:
                set_field((dynamic_cast<StorableObject *>(object))->id(),
                        (*it)->field, (*it)->integer);
                break;
            case Argument::TIME:
                set_field((dynamic_cast<StorableObject *>(object))->id(),
                        (*it)->field, (*it)->time);
                break;
            case Argument::ENUMERATION:
                set_field_enum((dynamic_cast<StorableObject *>(object))->id(),
                        (*it)->field, (*it)->string);
                break;
            }
        }

        (dynamic_cast<StorableObject *>(object))->load();

        return dynamic_cast<StorableObject *>(object);
    }

    virtual std::vector<StorableObject *>& search(std::vector<Argument *>& parameters) = 0;

    virtual StorableObject * object(const int id) const { return objects_[id]; }
};

};

