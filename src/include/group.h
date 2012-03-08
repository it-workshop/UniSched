#pragma once

#include <vector>

#include <abstractgroup.h>

namespace Core {

/**< @class Group
 * @brief Class keeps information about group of people.
 *
 * This group can be child group in contrast to AbstractGroup or Event.
 */
class Group: public AbstractGroup {
protected:
    void check_field(const std::string& name, const boost::any& value) const
        throw(boost::bad_any_cast, std::bad_cast);
public:
    Group(objid_t id, AbstractUI& ui):
            AbstractGroup(id, ui)
    {}
};

};
/*
namespace YAML {
    template<>
    struct convert<Core::Group> {
        static Node encode(const Core::Group& g)
        {
            Node node;
            node["name"] =
                dynamic_cast<const Core::FieldString &>(g.read("name")).value();
            return node;
        }
        static bool decode(const Node& node, Core::Group& g)
        {
            // Check if node is the right mask for class Person
            //if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            g.update(Core::FieldString("name", node["name"].as<std::string>()));
            return true;
        }
    };
}
*/
