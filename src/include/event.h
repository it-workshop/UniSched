#pragma once

#include <abstractgroup.h>

namespace Core {

/** @class Event
 * @brief Group of people, doing something in the some time.
 */
class Event: public AbstractGroup {
protected:
    void check_field(const std::string& name, const boost::any& value) const
        throw(boost::bad_any_cast, std::bad_cast);
public:
    Event (objid_t id, AbstractUI& ui) throw (std::bad_cast):
            AbstractGroup(id, ui)
    {
    }
};

};
/*
namespace YAML {
    template<>
    struct convert<Core::Event> {
        static Node encode(const Core::Event& ev)
        {
            Node node;
            node["name"] = 
                dynamic_cast<const Core::FieldString &>(ev.read("name")).value();
            node["begin"] = 
                dynamic_cast<const Core::FieldString &>(ev.read("begin")).value();
            node["duration"] =
                dynamic_cast<const Core::FieldString &>(ev.read("duration")).value();
            return node;
        }
        static bool decode(const Node& node, Core::Event& ev)
        {
            // Check if node is the right mask for class Person
            //if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            ev.update(Core::FieldString("begin", node["begin"].as<std::string>()));
            ev.update(Core::FieldString("duration", node["duration"].as<std::string>()));
            return true;
        }
    };
}
*/
