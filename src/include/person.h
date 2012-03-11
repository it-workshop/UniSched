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
    virtual const std::string link_field(const Object * object) const
            throw (std::bad_cast);
    virtual const std::string  back_link_field(const Object * object) const
            throw (std::bad_cast);
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
            node["birthday"] = boost::any_cast<const time_t &>(p.read("birthday"));
            //auto membership = boost::any_cast<const std::vector<Core::objid_t> &>(p.read("groups"));
            //for (int i = 0; i < membership.size(); i ++)
            //{
            //    node["groups"][i] = membership[i];
            //}
            return node;
        }
        static bool decode(const Node& node, Core::Person& p)
        {
            // Check if node is the right mask for class Person
            if (!node.IsMap()) return false;
//            if (!node.size() == 5) return false;
            p.update("name", node["name"].as<std::string>());
            p.update("surname", node["surname"].as<std::string>());
            p.update("sex", node["sex"].as<std::string>());
            p.update("birthday", node["birthday"].as<time_t>());
            /*
            for (int i = 0; i < node["groups"].size(); i ++)
            {
                p.connect(p.UI().object(node["groups"][i].as<int>()), true);
            }*/
            return true;
        }
    };
}

#endif /* WITH_YAML */

