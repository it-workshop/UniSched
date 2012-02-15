#pragma once

#include <vector>

#include <abstractgroup.h>

namespace Core {

/**< @class Group
 * @brief Class keeps information about group of people.
 */
class Group: public AbstractGroup {
private:
    FieldVector parent_groups_;

public:
    Group(const int id, Manager& manager):
            AbstractGroup(id, manager), parent_groups_("parent_groups")
    {
        parent_groups_ = 
            dynamic_cast<const FieldVector&>(pull("parent_groups"));
    }

    virtual const Field& read(const std::string& name) const throw (std::bad_cast);
    virtual void update(const Field& field) throw (std::bad_cast);
};

};

