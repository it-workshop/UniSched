#pragma once

#include <string>
#include <vector>

namespace Core {

class ManagersObject {
friend class Manager;
private:
    const int id_;
    class Manager& manager_;

protected:
    const int id() const { return id_; };

    const int get_field_int(const std::string name) const;
    const std::string get_field_string(const std::string name) const;
    const time_t get_field_time(const std::string name) const;
    const std::string get_field_enum(const std::string name) const;
    const ManagersObject * get_field_object(const std::string name) const;
    std::vector<ManagersObject *> get_field_vector(const std::string name) const;

    void set_field(const std::string name, const int value);
    void set_field(const std::string name, const std::string value);
    void set_field(const std::string name, const time_t value);
    void set_field_enum(const std::string name, const std::string);
    void set_field(const std::string name, ManagersObject * value);
    void set_field_vector(const std::string name, const std::vector<ManagersObject *>& vector);

    virtual void save() = 0;
    virtual void load() = 0;

public:

    ManagersObject(const int id, Manager& manager): id_(id), manager_(manager) {}
};

};

#include <manager.h>
