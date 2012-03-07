#pragma once

#include <abstractgroup.h>

namespace Core {

/** @class Event
 * @brief Group of people, doing something in the some time.
 */
class Event: public AbstractGroup {
private:
    FieldTime begin_;
                        /**< Begin of event. */
    FieldTime duration_;
                        /**< Duration of event. */
protected:
public:
    Event (const obj_t type, const objid_t id, AbstractUI& ui) throw (std::bad_cast):
            AbstractGroup(type, id, ui), begin_("begin"), duration_("duration")
                         /**< @copydoc AbstractGroup::AbstractGroup */
    {
        begin_ = dynamic_cast<const FieldTime&>(pull("begin"));
        duration_ = dynamic_cast<const FieldTime&>(pull("duration"));
    }

    virtual const Field& read(const std::string& name) const
        throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::read
                         * Specific fields names: "begin", "duration".
                         * Object type: FieldTime.
                         */

    virtual void update(const Field& field) throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::update
                         * Specific fields names: "begin", "duration".
                         * Object type: FieldTime.
                         */
};

};

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

