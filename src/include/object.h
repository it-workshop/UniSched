#pragma once

#include <string>
#include <map>
#include <boost/any.hpp>

#include <yaml-cpp/yaml.h>

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
                         * @internal This identificator must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */

    class AbstractUI& ui_;
                        /**< Manager of the objects.
                         * @internal This field must be used in pull and push
                         * methods only.
                         */
    std::map<const std::string, boost::any> fields_;
protected:
    const objid_t id() const { return id_; };
                        /**< @brief Get id of the object.
                         * @return id of object.
                         * @internal Use this method in the manager and storage
                         * classes only.
                         */
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

public:

    Object(const objid_t id, AbstractUI& ui):
        id_(id), ui_(ui)
                        /**< @brief Constructor.
                         * @param [in] id Identificator of the object.
                         * @param [in] ui Manager of objects.
                         */
    {}

    const boost::any& read(const std::string& name)
                        /**< @brief Get field of the object.
                         * @param [in] name Name of the field to get.
                         * @return Corresponding field.
                         */
    {
        return fields_[name];
    }

    void update(const std::string& name, const boost::any& value);
                        /**< @brief Change field of the object.
                         * @param [in] field Field to change.
                         */
};

};

/*
namespace YAML {
    template<>
    struct convert<Core::obj_t> {
        static Node encode(const Core::obj_t& ot)
        {
            Node node;
            switch (ot) {
            case Core::PERSON: node[0] = "Person"; return node;
            case Core::GROUP: node[0] = "Group"; return node;
            case Core::EVENT: node[0] = "Event"; return node;
            default: node[0] = "Unknown"; return node;
            }
            return node;
        }
        static bool decode(const Node& node, Core::obj_t& ot)
        {
            // Check if node is the right mask for Core::obj_t
            if (!node.IsScalar()) return false;
            if (!node.size() == 1) return false;
            const std::string type = node[0].as<std::string>();
            if (type == "Person") ot = Core::PERSON;
            else if (type == "Group") ot = Core::GROUP;
            if (type == "Event") ot = Core::EVENT;
            else ot = Core::UNKNOWN;
            return true;
        }
    };
  /* 
    template<> 
    struct convert<Core::objid_t> {
        static Node encode(const Core::objid_t& oid)
        {
            Node node;
            node[0] = (unsigned) oid;
            return node;
        }
        static bool decode(const Node& node, Core::objid_t& oid)
        {
            // Check if node is the right mask for Core::objid_t
            if (!node.IsScalar()) return false;
            if (!node.size() == 1) return false;
            oid = (const unsigned) node[0].as<unsigned>();
            return true;
        }
    };
    */
    /*
}
*/
#include <abstractui.h>

