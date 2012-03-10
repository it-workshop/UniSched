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
    Event (const objid_t id, AbstractUI& ui) throw (std::bad_cast):
            AbstractGroup(EVENT, id, ui)
    {}
};

};

#ifdef WITH_YAML

namespace YAML {
    template<>
    struct convert<Core::Event> {
        static Node encode(const Core::Event& ev)
        {
            Node node;
            node["name"] = boost::any_cast<const std::string &>(ev.read("name"));
            node["begin"] = boost::any_cast<const time_t &>(ev.read("begin"));
            node["duration"] = boost::any_cast<const time_t &>(ev.read("duration"));
            return node;
        }
        static bool decode(const Node& node, Core::Event& ev)
        {
            // Check if node is the right mask for class Event
            if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            ev.update("name", node["name"].as<std::string>());
            ev.update("begin", node["begin"].as<time_t>());
            ev.update("duration", node["duration"].as<time_t>());
            return true;
        }
    };
}

#endif /* WITH_YAML */
