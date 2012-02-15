#pragma once

#include <abstractgroup.h>

namespace Core {

class Event: public AbstractGroup {
private:
    FieldTime begin_;
    FieldTime duration_;

protected:
public:
    Event (const int id, Manager& manager) throw (std::bad_cast):
            AbstractGroup(id, manager), begin_("begin"), duration_("duration")
    {
        begin_ = dynamic_cast<const FieldTime&>(pull("begin"));
        duration_ = dynamic_cast<const FieldTime&>(pull("duration"));
    }

    virtual const Field& read(const std::string& name) const throw (std::bad_cast);
    virtual void update(const Field& field) throw (std::bad_cast);
};

};

