/** @file
 * @brief Core::Event class definition.
 * @author Derbenev Aleksander
 * @author Ter-Gabrielyan Arshavir
 * @date 2011-2012
 */

#pragma once

#include <abstractgroup.h>

namespace Core {

/** @class Event
 * @brief Group of people, doing something in the some time.
 *
 * Objects of this class keep the information about some event.
 * It's a name of event, time of start, duration and people and groups,
 * that take a part in this event.
 *
 * There is three fixed-type fields:
 *  - name(string),
 *  - start(time),
 *  - duration(time).
 *
 * Thre is two fields reserved for connections:
 *  - people (connections with Core::Person objects),
 *  - children_groups (connections with Core::Groups objects).
 */
class Event: public AbstractGroup {
protected:
    void check_field(const std::string& name, const boost::any& value) const
        throw(boost::bad_any_cast);
                /**< Check, can field with this name store this value.
                 *
                 * @param [in] name The name of the field.
                 * @param [in] value The value of the field.
                 * 
                 * Throws boost::bad_any_cast if name is equal to "name", but
                 * value is not a string, if name is equal to "start" or
                 * duration, but value is not a time, also if name is equal to
                 * "people" or "children_groups".
                 */
public:
    Event (const objid_t id, AbstractUI& ui) throw (std::bad_cast):
            AbstractGroup(EVENT, id, ui)
    {}
                /**< Constructor.
                 *
                 * @param [in] id Object's identificator is.
                 * @param [in] ui Object's manager is.
                 *
                 */
};

};


