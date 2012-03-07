#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <yaml-cpp/yaml.h>

#include <object.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public Object {
friend class AbstractGroup;
private:
    FieldString name_;
                            /**< Name of the person. */
    FieldString surname_;
                            /**< Surname of the person. */
    FieldEnum sex_;
                            /**< Person's sex. */
    FieldTime birthday_;
                            /**< Person birthday. Time in seconds from 00:00:00, 1 Jan, 1900. */
    FieldVector groups_;
                            /**< Person's groups. */

protected:
    void add_group(Object * group)
                            /**< Add group to person, call in AbstractGroup::add_person()
                             * @param [in] group to add.
                             */
    {
        groups_.add(group);
    }

    void del_group(Object * group)
                            /**< Delete group from person.
                             * @param [in] group.
                             */
    {
        groups_.del(group);
    }

public:
    Person(obj_t type, objid_t id, AbstractUI& ui) throw (std::bad_cast);
                            /**< @copydoc Object::Object */
   
    virtual const Field& read(const std::string& name) const
        throw (std::bad_cast);
                            /**< @copydoc Object::read */
    virtual void update(const Field& field) throw (std::bad_cast);
                            /**< @copydoc Object::update */
};

};

namespace YAML {
    template<>
    struct convert<Core::Person> {
        static Node encode(const Core::Person& p)
        {
            Node node;
            node["name"] = 
                dynamic_cast<const Core::FieldString &>(p.read("name")).value();
            node["surname"] =
                dynamic_cast<const Core::FieldString &>(p.read("surname")).value();
            node["sex"] =
                dynamic_cast<const Core::FieldString &>(p.read("sex")).value();
            return node;
        }
        static bool decode(const Node& node, Core::Person& p)
        {
            // Check if node is the right mask for class Person
            //if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            p.update(Core::FieldString("name", node["name"].as<std::string>()));
            p.update(Core::FieldString("surname", node["surname"].as<std::string>()));
            p.update(Core::FieldEnum("sex", node["sex"].as<std::string>()));
            return true;
        }
    };
}

