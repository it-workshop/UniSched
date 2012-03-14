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
protected:
    const std::string back_link_field(const Object *object) const
            throw (std::bad_cast);
    const bool disconnect_way(const std::string& name) const
            throw (std::bad_cast);
public:
    Group(objid_t id, AbstractUI& ui):
            AbstractGroup(GROUP, id, ui)
    {}
};

};



