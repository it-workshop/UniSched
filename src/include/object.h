#pragma once

#include <string>
#include <map>

#include <boost/any.hpp>

#ifdef WITH_YAML
#include <yaml-cpp/yaml.h>
#endif /* WITH_YAML */


namespace Core {

enum obj_t {UNKNOWN, PERSON, GROUP, EVENT};
typedef unsigned long int objid_t;

/**< @class Object
 * @brief Universal interface of core objects.
 */
class Object {
friend class AbstractUI;
friend class AbstractStorage;
private:
    objid_t id_;
                        /**< Identificator of the object.
                         * @internal This field must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */
    obj_t type_;
                        /**< Type of the object.
                         * @internal This field must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */

    class AbstractUI& ui_;
                        /**< Manager of the objects.
                         * @internal This field must be used in pull and push
                         * methods only.
                         */
    std::map<const std::string, boost::any> fields_;

    void update(const std::string& name, Object * object, const bool connect)
            throw (boost::bad_any_cast);

    void back_connect(Object * object, const bool connect) throw (std::bad_cast);

protected:
    virtual void check_field(const std::string& name,
            const boost::any& value) const
        throw(boost::bad_any_cast, std::bad_cast) = 0;
                        /**< @brief Check type and value of the field
                         * @param [in] name Name of the field.
                         * @param [in] value Value of the field.
                         *
                         * Must throw boost::any_cast if field has incorrect
                         * type or value.
                         *
                         * @code{.cpp}
                         *
                         * class SomeCoreObject : public Core::Object {
                         * protected:
                         *     virtual void check_field(const std::string& name,
                         *             const boost::any& value) const
                         *             throw(boost::bad_any_cast);
                         * public:
                         *     SomeCoreObject(const objid_t id, AbstractUI& ui):
                         *         Object(id, ui)
                         *     {}
                         * };
                         *
                         * void
                         * SomeCoreObject::check_field(const std::string& name,
                         *                      const boost::any& value) const
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
                         * }
                         *
                         * @endcode
                         */
    virtual const std::string link_field(const Object * object) const
            throw (std::bad_cast) = 0;
                        /**< @brief Check if one object could link another one 
                         * and return name of the corresponding field of first
                         * object.
                         * @param [in] object Object to check.
                         * 
                         * This method must throw std::bad_cast, when connect
                         * can not be set.
                         */
    virtual const std::string back_link_field(const Object * object) const
            throw (std::bad_cast) = 0;
                        /**< @brief Check if one object links another one and
                         * return name of the corresponding field of first
                         * object on the second link.
                         *
                         * This method must throw std::bad_cast, when connect
                         * can not be set.
                         */
public:
    const objid_t id() const { return id_; }
                        /**< @brief Get id of the object.
                         * @return id of object.
                         * @internal Use this method in the manager and storage
                         * classes only.
                         */
    const obj_t type() const { return type_; }
                        /**< @brief Get type of the object.
                         * @return type of object.
                         * @internal Use this method in the manager and storage
                         * classes only.
                         */
    const AbstractUI& UI() const { return ui_; }
                        /**< @brief Get User Interface which manages the object.
                         * @return User Interface of object.
                         */
    Object(const obj_t type, const objid_t id, AbstractUI& ui):
        type_(type), id_(id), ui_(ui)
                        /**< @brief Constructor.
                         * @param [in] id Identificator of the object.
                         * @param [in] ui Manager of objects.
                         */
    {}

    const boost::any read(const std::string& name) const
                        /**< @brief Get field of the object.
                         * @param [in] name Name of the field to get.
                         * @return Corresponding field.
                         */
    {
        return (*fields_.find(name)).second;
    }

    const std::map<const std::string,boost::any>& read() const
    {
        return fields_;
    }

    void update(const std::string& name, const boost::any& value);
                        /**< @brief Change field of the object.
                         * @param [in] field Field to change.
                         */
    void connect(Object * object, const bool connect = true)
            throw (std::bad_cast);

    void disconnect(Object *object) throw (std::bad_cast);
};

};

#include <abstractui.h>

