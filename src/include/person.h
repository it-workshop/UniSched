#pragma once

#include <string>
#include <sstream>
#include <vector>

#ifdef WITH_YAML
#include <yaml-cpp/yaml.h>
#endif /* WITH_YAML */

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

#ifdef WITH_YAML

namespace YAML {
    template<>
    struct convert<Core::Person> {
        static Node encode(const Core::Person& p)
        {
            Node node;
            node["name"] = boost::any_cast<const std::string &>(p.read("name")); 
            node["surname"] = boost::any_cast<const std::string &>(p.read("surname"));
            node["sex"] = boost::any_cast<const std::string &>(p.read("sex"));
            return node;
        }
        static bool decode(const Node& node, Core::Person& p)
        {
            // Check if node is the right mask for class Person
            if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            p.update("name", node["name"].as<std::string>());
            p.update("surname", node["surname"].as<std::string>());
            p.update("sex", node["sex"].as<std::string>());
            return true;
        }
    };
}

#endif /* WITH_YAML */

