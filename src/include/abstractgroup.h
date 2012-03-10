#pragma once

#include <string>
#include <vector>

#include <object.h>
#include <person.h>

/**@namespace Core
 * @brief Core model classes.
 */
namespace Core {

/**@class AbstractGroup
 * @brief Base group functionality. You need to use it instead of Group or
 * Event in most cases.
 *
 * This is a generalization of groups and events. It allows to work easy with
 * them. It have not parent group as an Event, but Group have.
 */
class AbstractGroup: public Object {
protected:
    void check_field(const std::string& name, const boost::any& value) const
            throw(boost::bad_any_cast, std::bad_cast);
    virtual const std::string link_field(const Object *object) const
            throw (std::bad_cast);
    virtual const std::string back_link_field(const Object *object) const
            throw (std::bad_cast);
public:
    AbstractGroup(const obj_t type, const objid_t id, AbstractUI& ui);
                        /**< @brief Constructor
                         * @param [in] id AbstractUIs object`s identificator.
                         * @param [in] ui Storage.
                         * @internal This constructor called from inherited
                         * classes.
                         */
};

};

