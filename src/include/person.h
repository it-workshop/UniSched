#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <object.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public Object {
protected:
    virtual void check_field(const std::wstring& name, const boost::any& value)
            const throw(boost::bad_any_cast);
    virtual const std::wstring link_field(const Object * object) const
            throw (std::bad_cast);
    virtual const std::wstring  back_link_field(const Object * object) const
            throw (std::bad_cast);
    virtual const bool disconnect_way(const std::wstring& name) const
            throw (std::bad_cast);
public:
    Person(objid_t id, AbstractUI& ui) throw (std::bad_cast);
                            /**< @copydoc Object::Object */
};

};

