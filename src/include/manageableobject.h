#pragma once

#include <string>
#include <vector>

namespace Core {

class ManageableObject {
friend class Manager;
private:
    const int id_;
    class Manager& manager_;

protected:
    const int id() const { return id_; };

    const class Field& pull(const std::string& name) const;

    void push(const class Field& field);

public:

    ManageableObject(const int id, Manager& manager): id_(id), manager_(manager)
    {}

    virtual const Field& read(const std::string& name) const = 0;
    virtual void update(const Field& field) = 0;
};

};

#include <manager.h>
#include <field.h>
