#pragma once

#include <abstractgroup.h>

namespace Core {

/** @class Event
 * @brief Group of people, doing something in the some time.
 */
class Event: public AbstractGroup {
protected:
    void check_field(const std::string& name, const boost::any& value) const
        throw(boost::bad_any_cast, std::bad_cast);
public:
    Event (const objid_t id, AbstractUI& ui) throw (std::bad_cast):
            AbstractGroup(EVENT, id, ui)
    {}
};

};


