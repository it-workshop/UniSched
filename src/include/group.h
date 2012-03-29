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
    virtual void check_field(const std::wstring& name, const boost::any& value)
            const throw (boost::bad_any_cast);
    virtual const std::wstring back_link_field(const Object *object) const
            throw (std::bad_cast);
    virtual const bool disconnect_way(const std::wstring& name) const
            throw (std::bad_cast);
public:
    Group(objid_t id, AbstractUI& ui):
            AbstractGroup(GROUP, id, ui)
    {}
};

};



