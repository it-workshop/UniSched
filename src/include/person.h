/** @file
 * @brief Core::Person class definition.
 * @author Derbenev Aleksander
 * @author Ter-Gabrielyan Arshavir
 * @date 2011-2012
 */
#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <object.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 *
 * Person is the core object. It have methods
 * read, update, connect and disconnect like any other object.
 *
 * Person has some fixed fields:
 *     name (string),
 *     surname (string),
 *     sex (string "MALE" or "FEMALE"),
 *     birthday (time).
 * It also can be connected with groups and events (field "groups").
 */
class Person: public Object {
protected:
    virtual void check_field(const std::string& name, const boost::any& value)
            const throw(boost::bad_any_cast);
        /**< Check field name and value.
         *
         * @param [in] name Name of the field.
         * @param [in] value New value of the field.
         *
         * It throws boost::bad_any_cast if @a name == "groups", or
         * value has incorrect type for fields name, surname (strings), sex
         * ("MALE or "FEMALE") or birthday (time)
         */
    virtual const std::string link_field(const Object * object) const
            throw (std::bad_cast);
        /**< Get name of the connection field.
         *
         * @param [in] object Object to connect with.
         * @return "groups" if @a object is an instance of AbstractGroup.
         *
         * Throws std::bad_cast if @a object is not instance of AbstractGroup.
         */
    virtual const std::string  back_link_field(const Object * object) const
            throw (std::bad_cast);
        /**< Get name of the feedback connection field
         *
         * @param [in] object Object to connect with.
         * @return "groups" if @a object is an instance of AbstractGroup.
         *
         * Throws std::bad_cast if @a object is not instance of AbstractGroup.
         */
    virtual const bool disconnect_way(const std::string& name) const
            throw (std::bad_cast);
        /**< Get direction of the disconnect operation.
         * @param [in] name Name of the connection field.
         * @return true if @a name == "groups".
         *
         * Any direction of this disconnect operation will be right.
         *
         * Throws std::bad_cast if @a name != "groups" because Person can be
         * connected only with AbstractGroup.
         */
public:
    Person(objid_t id, AbstractUI& ui) throw (std::bad_cast);
        /**< Constructor.
         * @param [in] id Object's id.
         * @param [in] ui Object's manager.
         */
};

};

