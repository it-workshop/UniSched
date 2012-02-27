#pragma once

#include <abstractgroup.h>

namespace Core {

/** @class Event
 * @brief Group of people, doing something in the some time.
 */
class Event: public AbstractGroup {
private:
    FieldTime begin_;
                        /**< Begin of event. */
    FieldTime duration_;
                        /**< Duration of event. */
protected:
public:
    Event (const int id, Manager& manager) throw (std::bad_cast):
            AbstractGroup(id, manager), begin_("begin"), duration_("duration")
                        /**< @brief Constructor. */
    {
        begin_ = dynamic_cast<const FieldTime&>(pull("begin"));
        duration_ = dynamic_cast<const FieldTime&>(pull("duration"));
    }

    virtual const Field& read(const std::string& name) const
        throw (std::bad_cast);
                        /**< @copydoc Core::AbstractGroup::read
                         * Specific fields names: "begin", "duration".
                         * Object type: Core::FieldTime.
                         */

    virtual void update(const Field& field) throw (std::bad_cast);
                        /**< @copydoc Core::AbstractGroup::update
                         * Specific fields names: "begin", "duration".
                         * Object type: Core::FieldTime.
};

};

