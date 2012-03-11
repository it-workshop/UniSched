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
/* TODO: Add database class to friend when create this. */
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

    void back_connect(Object * object, const bool connect) throw (std::bad_cast)
    {
        update(back_link_field(object), object, connect);
    }

protected:
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
    void connect(Object * object, const bool connect = true) throw (std::bad_cast)
    {
        update(link_field(object), object, connect);
        object->back_connect(this, connect);
    }

    void disconnect(Object *object)
        throw (std::bad_cast)
    {
        connect(object, false);
    }

};

};

#ifdef WITH_YAML

namespace YAML {
    template<>
    struct convert<std::map<const std::string, boost::any>> {
        static Node encode(const std::map<const std::string, boost::any>& fields) 
        { // This convertion must match only for the object's VCard
            Node node;
            // Shouldn't I write something about const_iterator? Nah
            for (auto iter = fields.begin(); iter != fields.end(); iter ++)
            {
                // Strings
                if (iter->first == "name" or
                    iter->first == "surname" or
                    iter->first == "sex")
                    node[iter->first] = boost::any_cast<const std::string &>(iter->second);
                else 
                // Dates&Times
                if (iter->first == "begin" or
                    iter->first == "duration" or
                    iter->first == "birthday")
                    node[iter->first] = boost::any_cast<const time_t &>(iter->second);
                else
                // Sequences
                if (iter->first == "groups" or
                    iter->first == "parent_groups" or
                    iter->first == "child_groups" or
                    iter->first == "people")
                    for (int i = 0; i < iter->first.size(); i ++)
                    {
                        node[iter->first] = boost::any_cast<const std::vector<Core::objid_t> &>(iter->second) [i];
                    }
            }

            return node;
        }
        static bool decode(const Node& node, std::map<const std::string, boost::any>& fields)
        { /* TODO: Make the loop to call bool YAML::decode(const YAML::Node& node, Core::Object)
                   instead of parsing everything again. */
            if (!node.IsMap()) return false;
            for (auto iter = node.begin(); iter != node.end(); iter ++)
            {
                if (iter->second.IsSequence()) // is sequence
                    fields[iter->second.as<std::string>()] = iter->second.as<std::vector<Core::objid_t>>();
                else // is scalar 
                {
                    if (iter->first.as<std::string>() == "birthday" or 
                        iter->first.as<std::string>() == "begin" or 
                        iter->first.as<std::string>() == "duration") 
                         fields[iter->first.as<std::string>()] = iter->second.as<time_t>();
                    else fields[iter->first.as<std::string>()] = iter->second.as<std::string>();
                }
            }
            return true;
        }
    };

    template<>
    struct convert<boost::any> {
        static Node encode(const boost::any& a)
        { // Just in case someone forgets about converting boost::any to std::string
            Node node;
            node = boost::any_cast<const std::string &>(a);
            return node;
        }
        static bool decode(const Node& node, boost::any& a)
        { // Currently works only with scalar boost::any-args
            if (!node.IsScalar()) return false;
            a = node.as<std::string>();
            return true;
        }
    };

    template<>
    struct convert<Core::obj_t> {
        static Node encode(const Core::obj_t& ot)
        {
            Node node;
            switch (ot) {
            case Core::PERSON: node = "Person"; return node;
            case Core::GROUP: node = "Group"; return node;
            case Core::EVENT: node = "Event"; return node;
            default: node = "Unknown"; return node;
            }
            return node;
        }
        static bool decode(const Node& node, Core::obj_t& ot)
        {
            // Check if node is the right mask for Core::obj_t
            if (!node.IsScalar()) return false;
            auto type = node.as<std::string>();
                 if (type == "Person") ot = Core::PERSON;
            else if (type == "Group")  ot = Core::GROUP;
            else if (type == "Event")  ot = Core::EVENT;
            else                       ot = Core::UNKNOWN;
            return true;
        }
    };
}

#endif /* WITH_YAML */

#include <abstractui.h>

