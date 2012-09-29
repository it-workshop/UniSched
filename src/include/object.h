/** @file
 * @brief Core::Object, Core::obj_t and Core::objid_t definition.
 * @author Derbenev Aleksander
 * @author Mosyagin Igor
 * @author Ter-Gabrielyan Arshavir
 * @date 2012
 */

#pragma once

#include <string>
#include <map>

#include <boost/any.hpp>

/** @namespace Core
 * Kernel of the project.
 *
 * It contains the objects and modules model implementations.
 */
namespace Core {

/** @enum obj_t
 * Object type.
 *
 * Describes types of objects known by the core.
 */
enum obj_t
{
    UNKNOWN,    /**< Unknown object.
                 * @attention It must not be used anywhere!
                 */
    PERSON,     /**< Person.
                 * Must be used in the Core::Person class
                 */
    GROUP,      /**< Group.
                 * Must be used in the Core::Group class
                 */
    EVENT       /**< Event.
                 * Must be used in the Core::Event class
                 */
};

/** @typedef objid_t
 * Object id type.
 *
 * Used for store, load and search objects.
 */
typedef unsigned long int objid_t;

/** @class Object
 * @brief Universal interface of core objects.
 *
 * @class Object
 * This is a base class for all core objects.
 *
 * We use the REST conception of the interface.
 *
 * Every object inherits from this one next methods:
 * read, update, connect and disconnect.
 * 
 * Use read method to get values of fields.
 * Use update method to change values of simple fields.
 * Use connect and disconnect methods to create or delete
 * links between the objects.
 *
 * Thouse methods are not virtual. They are works usually for all
 * objects. You have not to know the type of object for any operation.
 *
 * Specific behavior of the object have to be implemented in some
 * protected pure virtual methods (check_field, link_field,
 * back_link_field and disconnect_way).
 *
 * The Core::AbstractUI is a fabric and the manager of the objects.
 *
 * @see Core::AbstractUI
 * @see Core::AbstractStorage
 */
class Object {
friend class AbstractUI;
friend class AbstractStorage;
private:
    const objid_t id_;
                        /**< Identificator of the object.
                         *
                         * @internal This field must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */
    const obj_t type_;
                        /**< Type of the object.
                         *
                         * @internal This field must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */

    class AbstractUI& ui_;
                        /**< Manager of the objects.
                         *
                         * @internal This field must be used in pull and push
                         * methods only.
                         */
    std::map<const std::string, boost::any> fields_;
                        /**< Fields of the objects.
                         *
                         * @internal Don't use it anywhere except this class.
                         */

    void update(const std::string& name, Object * object, const bool connect)
            throw (boost::bad_any_cast);
                        /**< @brief Update connection field and call back_update
                         * of @a object.
                         *
                         * @internal Don't use it anywhere except this class.
                         */

    void back_update(const std::string& name, Object * object, const bool connect)
            throw (boost::bad_any_cast);
                        /**< Update second connection field.
                         *
                         * @internal Don't use it anywhere except this class.
                         */

    void back_connect(Object * object, const bool connect) throw (std::bad_cast);
                        /**< @brief Find name of the second connection field
                         * and call update.
                         *
                         * @internal Don't use it anywhere except this class.
                         */

protected:
    virtual void check_field(const std::string& name,
            const boost::any& value) const
        throw(boost::bad_any_cast) = 0;
                        /**< @brief Check type and value of the field
                         * @param [in] name Name of the field.
                         * @param [in] value Value of the field.
                         *
                         * Must throw boost::any_cast if field has incorrect
                         * type or value.
                         *
                         * @attention Make sure that fields that changed by
                         * connect and disconnect methods cannot be changed
                         * by simple update. Throw exception for thouse fields.
                         *
                         * @code
                         *
                         * class Person : public Core::Object {
                         * protected:
                         *     virtual void check_field(const std::string& name,
                         *             const boost::any& value) const
                         *             throw(boost::bad_any_cast);
                         * public:
                         *     Person(const objid_t id, AbstractUI& ui):
                         *         Object(PERSON, id, ui)
                         *     {}
                         * };
                         *
                         * void
                         * Person::check_field(const std::string& name,
                         *                      const boost::any& value) const
                         *      throw (boost::bad_any_cast);
                         * {
                         *     if ("name" == name)
                         *     {
                         *         if (value.type() != typeid(std::string))
                         *         {
                         *             throw boost::bad_any_cast();
                         *         }
                         *         return;
                         *     }
                         *     if ("birthday" == name)
                         *     {
                         *         if (value.type() != typeid(time_t))
                         *         {
                         *             throw boost::bad_any_cast();
                         *         }
                         *         return;
                         *     }
                         *     if ("sex" == name)
                         *     {
                         *         if (boost::any_cast<std::string>(value)
                         *                 != "MALE"
                         *             && boost::any_cast<std::string>(value)
                         *                 != "FEMALE")
                         *         {
                         *             throw boost::bad_any_cast();
                         *         }
                         *         return;
                         *     }
                         *     if ("groups" == name)
                         *     {
                         *         throw boost::bad_any_cast();
                         *     }
                         * }
                         *
                         * @endcode
                         */
    virtual const std::string link_field(const Object * object) const
            throw (std::bad_cast) = 0;
                        /**< @brief Get connection field name.
                         *
                         * @param [in] object Object to check.
                         *
                         * Check if one object could link another one 
                         * and return name of the corresponding field of first
                         * object.
                         * 
                         * This method must throw std::bad_cast, when connect
                         * can not be set.
                         *
                         * Example:
                         * @code
                         * class Person : public Core::Object {
                         * protected:
                         *     virtual const std::string
                         *     link_field(const Object *object) const
                         *         throw (std:;bad_cast);
                         * public:
                         *     Person(objid_t id, Core::AbstractUI &ui):
                         *         Object(PERSON, id, ui)
                         *     {}
                         * };
                         *
                         * const std::string
                         * Person::link_field(const Object *object) const
                         *     throw (std::bad_cast)
                         * {
                         *     if (typeid(object) == typeid(AbstractGroup))
                         *     {
                         *         return "groups";
                         *     }
                         *     throw std::bad_cast();
                         * }
                         * @endcode
                         *
                         * @internal Implement this method in the child class,
                         * but don't use it anywhere except this one.
                         */
    virtual const std::string back_link_field(const Object * object) const
            throw (std::bad_cast) = 0;
                        /**< @brief Get second connection field name.
                         *
                         * @param [in] object Object to check.
                         *
                         * Check if one object links another one and
                         * return name of the corresponding field of first
                         * object on the second link.
                         *
                         * This method must throw std::bad_cast, when connect
                         * can not be set.
                         *
                         * Example:
                         * @code
                         * class Person : public Core::Object {
                         * protected:
                         *     virtual const std::string
                         *     back_link_field(const Object * object) const
                         *         throw (std::bad_cast);
                         * public:
                         *     Person(objid_t id, Core::AbstractUI &ui):
                         *         Object(PERSON, id, ui)
                         *     {}
                         * };
                         *
                         * const std::string
                         * back_link_field(const Object * object) const
                         *     throw (std::bad_cast)
                         * {
                         *     if (typeid(object) == typeid(AbstractGroup))
                         *     {
                         *         return "groups";
                         *     }
                         *     throw std::bad_cast();
                         * }
                         * @endcode
                         *
                         * @internal Implement this method in the child class,
                         * but don't use it anywhere except this one.
                         */
    virtual const bool disconnect_way(const std::string& name) const
            throw (std::bad_cast) = 0;
                        /**< @brief Get direction of disconnect operation.
                         *
                         * @param [in] name of the field.
                         * @return True if objects disconnects in forward
                         * direction.
                         *
                         * Check if connections in fields with given
                         * name must be disconnected in the forward or backward
                         * direction.
                         *
                         * Example:
                         * @code
                         * class Group : public AbstractGroup {
                         * protected:
                         *     virtual const bool
                         *     disconnect_way(const std::string& name) const
                         *         throw (std::bad_cast);
                         * public:
                         *     Group(objid_t id, Core::AbstractUI &ui):
                         *         AbstractGroup(GROUP, id, ui)
                         *     {}
                         * };
                         *
                         * const bool
                         * Group::disconnect_way(const std::string& name) const
                         *         throw (std::bad_cast)
                         * {
                         *     if (name == "parent_groups")
                         *     {
                         *         return false;
                         *     }
                         *     return AbstractGroup::disconnect_way(name);
                         * }
                         * @endcode
                         *
                         * @internal Implement this method in the child class,
                         * but don't use it anywhere except this one.
                         */
public:
    const objid_t id() const { return id_; }
                        /**< @brief Get id of the object.
                         *
                         * @return id of object.
                         */
    const obj_t type() const { return type_; }
                        /**< @brief Get type of the object.
                         *
                         * @return type of object.
                         */
    const AbstractUI& UI() const { return ui_; }
                        /**< @brief Get User Interface which manages the object.
                         *
                         * @return User Interface of object.
                         */
    Object(const obj_t type, const objid_t id, AbstractUI& ui):
        type_(type), id_(id), ui_(ui)
    {}
                        /**< @brief Constructor.
                         *
                         * @param [in] type Type of object.
                         * @param [in] id Identificator of the object.
                         * @param [in] ui Manager of objects.
                         *
                         * FIXME: Why it's in a public section? I think that it
                         * must be in private section.
                         */

    void cleanup();
                        /**< @brief Cleanup connections.
                         * 
                         * @attention Call it before delete object.
                         *
                         * @attention This code is not in the destructor because
                         * it use some virtual methods and it must not be called
                         * when object just deletes. It must be called when
                         * object is removed from database.
                         *
                         * FIXME: Why it's in a public section? I think that it
                         * must be in private section.
                         */

    const boost::any read(const std::string& name) const
    {
        auto it = fields_.find(name);
        return it != fields_.end() ? it->second : boost::any();
    }
                        /**< @brief Get field of the object.
                         *
                         * @param [in] name Name of the field to get.
                         * @return Corresponding field.
                         */

    const std::map<const std::string,boost::any>& read() const
    {
        return fields_;
    }
                        /**< @brief Get all fields of the objects.
                         *
                         * @return All fields of the object.
                         */

    void update(const std::string& name, const boost::any& value)
        throw (boost::bad_any_cast);
                        /**< @brief Change field of the object.
                         *
                         * @param [in] name Name of the field to change.
                         * @param [in] value New value of the field.
                         *
                         * It calls check_field to check, can this field be
                         * changed directly and can value be corresponding type.
                         * It can throw std::bad_any_cast if this field can be
                         * changed by this method or value has incorrect type.
                         */

    void update(const std::map<std::string, boost::any>& fields)
            throw (boost::bad_any_cast);
                        /**< @brief bulk change fields of the object.
                         *
                         * @param [in] fields map of fields to change.
                         *
                         * @see Core::Object::update(core std::string,
                         *  const boost::any&) for more.
                         */

    void connect(Object * object, const bool connect = true)
            throw (std::bad_cast);
                        /**< @brief Connect (or disconnect) object with another
                         * one.
                         *
                         * @param [in] object Object to connect (or disconnect)
                         * with.
                         * @param [in] connect Indicates connect or disconnect
                         * this objects.
                         *
                         * This method calls
                         *
                         * @code
                         * this->link_field(object)
                         * @endcode
                         *
                         * to get the name of the field in which connections
                         * with corresponding type of objects are stored. Than
                         * it calls
                         *
                         * @code
                         * this->update(name, object, connect)
                         * @endcode
                         *
                         * to add into or remove @a object from corresponding
                         * field. Than it calls
                         *
                         * @code
                         * object->back_connect(this, @a)
                         * @endcode
                         *
                         * to make the feedback from the @a object to this one.
                         *
                         * It can throw std::bad_cast exception if @a object
                         * cannot be connected to or disconnected from this one.
                         *
                         * @attention It can throw boost:bad_any_cast if the
                         * needed field of the some objects contain invalid type
                         * for connecting. You have to check check_field
                         * function to make sure that you deny to change
                         * directly thouse fields.
                         */

    void disconnect(Object *object) throw (std::bad_cast);
                        /**< @brief Disconnects this object from the @a object.
                         *
                         * @param [in] object Object to disconnect from.
                         *
                         * It only calls
                         *
                         * @code
                         * connect(object, false);
                         * @endcode
                         *
                         * @see Core::Object::connect for more information.
                         */
};

};

#include <abstractui.h>

