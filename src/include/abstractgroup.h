/** @file
 * @brief Core::AbstractGroup class definition.
 * @author Derbenev Aleksander
 * @author Ter-Gabrielyan Arshavir
 * @date 2011-2012
 */

#pragma once

#include <string>
#include <vector>

#include <object.h>
#include <person.h>

namespace Core {

/**@class AbstractGroup
 * @brief Base group functionality. You need to use it instead of Group or
 * Event in most cases.
 *
 * This is a generalization of groups and events. It allows to work easy with
 * them. It have not parent group as an Event, but Group have.
 *
 * @internal Do not create objects of this class anywhere! Use Core::Event and
 * Core::Group classes instead!
 */
class AbstractGroup: public Object {
protected:
    void check_field(const std::string& name, const boost::any& value) const
            throw(boost::bad_any_cast);
                        /**< Check can field with this name has this value.
                         *
                         * @param [in] name The name of the field.
                         * @param [in] value The value of the field.
                         *
                         * Throws boost::bad_any_cast if @a name is equal to
                         * "people" or "children_groups".
                         *
                         * @internal It's called by Core::Object::update
                         */
    virtual const std::string link_field(const Object *object) const
            throw (std::bad_cast);
                        /**< Get name of the connection field.
                         *
                         * @param [in] object The object to connect with.
                         * @return "people" if object is instance of
                         * Core::Person or "children_groups" if object is
                         * instance of the this class.
                         *
                         * Throws std::bad_cast, if object has unknown type.
                         */
    virtual const std::string back_link_field(const Object *object) const
            throw (std::bad_cast);
                        /**< Get name of the second connection field.
                         *
                         * @param [in] object The object to connect with.
                         * @return "people if object is instance of
                         * Core::Person.
                         *
                         * Throws std::bad_cast, if object is not an instance of
                         * Core::Person.
                         */
    virtual const bool disconnect_way(const std::string& name) const
            throw (std::bad_cast);
                        /**< Get the direction of the disconnect mehdod.
                         *
                         * @param [in] name Name of the connection field.
                         * @return [true] if name is equal to "people" or
                         * "children_groups".
                         *
                         * Throws std::bad_cast, if name is not equal to
                         * "people" or "children_groups".
                         */
public:
    AbstractGroup(const obj_t type, const objid_t id, AbstractUI& ui);
                        /**< Constructor.
                         *
                         * @param [in] type Type of the object.
                         * @param [in] id AbstractUIs object`s identificator.
                         * @param [in] ui Storage.
                         *
                         * FIXME: I think, that this constructor must be in the
                         * protected section. Why is it in the public?
                         *
                         * @internal This constructor called from inherited
                         * classes.
                         */
};

};

