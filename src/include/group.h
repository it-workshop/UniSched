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
private:
    FieldVector parent_groups_;

public:
    Group(const obj_t type, const objid_t id, AbstractUI& ui):
            AbstractGroup(type, id, ui), parent_groups_("parent_groups")
                        /**< @copydoc AbstractGroup::AbstractGroup */
    {
        parent_groups_ = 
            dynamic_cast<const FieldVector&>(pull("parent_groups"));
    }

    virtual const Field& read(const std::string& name) const
            throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::read
                         *
                         * Possible names are: parent_group.
                         */

    virtual void update(const Field& field) throw (std::bad_cast);
                        /**< @copydoc AbstractGroup::update
                         * 
                         * Possible names are: parent_group.
                         */
};

};

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

