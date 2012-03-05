#pragma once

#include <vector>

#include <abstractgroup.h>

namespace Core {

/**< @class Group
 * @brief Class keeps information about group of people.
 *
 * This group can be child group in contrast to AbstractGroup or Event.
 */
class Group: public AbstractGroup {
private:
    FieldVector parent_groups_;

public:
    Group(const int id, AbstractUI& ui):
            AbstractGroup(id, ui), parent_groups_("parent_groups")
                        /**< @copydoc AbstractGroup::AbstractGroup */
    {
        parent_groups_ = 
            dynamic_cast<const FieldVector&>(pull("parent_groups"));
    }

    virtual const Field& read(const std::string& name) const
            throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::read
                         *
                         * Possible names are: parent_group.
                         */

    virtual void update(const Field& field) throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::update
                         * 
                         * Possible names are: parent_group.
                         */
};

};

