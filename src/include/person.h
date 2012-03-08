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
protected:
    virtual void check_field(const std::string& name, const boost::any& value)
            const throw(boost::bad_any_cast);
public:
    Person(objid_t id, AbstractUI& ui) throw (std::bad_cast);
                            /**< @copydoc Object::Object */
};

};

/*
 * What the fuck? Why does this makes errors on build?
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
*/

