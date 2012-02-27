#pragma once

#include <string>
#include <vector>

namespace Core {

class Object {
friend class AbstractUI;
private:
    const int id_;
    class AbstractUI& ui_;

protected:
    const int id() const { return id_; };

    const class Field& pull(const std::string& name) const;

    void push(const class Field& field);

public:

    Object(const int id, AbstractUI& ui): id_(id), ui_(ui)
    {}

    virtual const Field& read(const std::string& name) const = 0;
    virtual void update(const Field& field) = 0;
};

};

#include <abstractui.h>
#include <field.h>
