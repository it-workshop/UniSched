#ifdef WITH_YAML

#include <yaml-cpp/yaml.h>

#include <object.h>
#include <person.h>
#include <group.h>
#include <event.h>

namespace YAML {
   /*--------------------------------------------------*/
  /*               General Convertations              */
 /*--------------------------------------------------*/
    template<>
    struct convert<std::map<const std::string, boost::any>> {
        static Node encode(const std::map<const std::string, boost::any>& fields) 
        { // This convertion must match only for the object's VCard
            Node node;
            // Shouldn't I write something about const_iterator? Nah
            for (auto iter = fields.begin(); iter != fields.end(); iter ++)
            {
                // Strings
                if (iter->first == "name" or
                    iter->first == "surname" or
                    iter->first == "sex")
                    node[iter->first] = boost::any_cast<const std::string &>(iter->second);
                else 
                // Dates&Times
                if (iter->first == "begin" or
                    iter->first == "duration" or
                    iter->first == "birthday")
                    node[iter->first] = boost::any_cast<const time_t &>(iter->second);
                else
                // Sequences
                if (iter->first == "groups" or
                    iter->first == "parent_groups" or
                    iter->first == "child_groups" or
                    iter->first == "people")
                    for (int i = 0; i < iter->first.size(); i ++)
                    {
                        node[iter->first] = boost::any_cast<const std::vector<Core::objid_t> &>(iter->second) [i];
                    }
            }

            return node;
        }
        static bool decode(const Node& node, std::map<const std::string, boost::any>& fields)
        { /* TODO: Make the loop to call bool YAML::decode(const YAML::Node& node, Core::Object)
                   instead of parsing everything again. */
            if (!node.IsMap()) return false;
            for (auto iter = node.begin(); iter != node.end(); iter ++)
            {
                if (iter->second.IsSequence()) // is sequence
                    fields[iter->second.as<std::string>()] = iter->second.as<std::vector<Core::objid_t>>();
                else // is scalar 
                {
                    if (iter->first.as<std::string>() == "birthday" or 
                        iter->first.as<std::string>() == "begin" or 
                        iter->first.as<std::string>() == "duration") 
                         fields[iter->first.as<std::string>()] = iter->second.as<time_t>();
                    else fields[iter->first.as<std::string>()] = iter->second.as<std::string>();
                }
            }
            return true;
        }
    };

    template<>
    struct convert<boost::any> {
        static Node encode(const boost::any& a)
        { // Just in case someone forgets about converting boost::any to std::string
            Node node;
            node = boost::any_cast<const std::string &>(a);
            return node;
        }
        static bool decode(const Node& node, boost::any& a)
        { // Currently works only with scalar boost::any-args
            if (!node.IsScalar()) return false;
            a = node.as<std::string>();
            return true;
        }
    };

    template<>
    struct convert<Core::obj_t> {
        static Node encode(const Core::obj_t& ot)
        {
            Node node;
            switch (ot) {
            case Core::PERSON: node = "Person"; return node;
            case Core::GROUP: node = "Group"; return node;
            case Core::EVENT: node = "Event"; return node;
            default: node = "Unknown"; return node;
            }
            return node;
        }
        static bool decode(const Node& node, Core::obj_t& ot)
        {
            // Check if node is the right mask for Core::obj_t
            if (!node.IsScalar()) return false;
            auto type = node.as<std::string>();
                 if (type == "Person") ot = Core::PERSON;
            else if (type == "Group")  ot = Core::GROUP;
            else if (type == "Event")  ot = Core::EVENT;
            else                       ot = Core::UNKNOWN;
            return true;
        }
    };
    
   /*-------------------------------------------------*/
  /*            Core::Person Convertations           */
 /*-------------------------------------------------*/
    template<>
    struct convert<Core::Person> {
        static Node encode(const Core::Person& p)
        {
            Node node;
            node["name"] = boost::any_cast<const std::string &>(p.read("name")); 
            node["surname"] = boost::any_cast<const std::string &>(p.read("surname"));
            node["sex"] = boost::any_cast<const std::string &>(p.read("sex"));
            node["birthday"] = boost::any_cast<const time_t &>(p.read("birthday"));
            //auto membership = boost::any_cast<const std::vector<Core::Group> &>(p.read("groups"));
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

   /*-------------------------------------------------*/
  /*             Core::Group Convertations           */
 /*-------------------------------------------------*/
    template<>
    struct convert<Core::Group> {
        static Node encode(const Core::Group& g)
        {
            Node node;
            node["name"] = boost::any_cast<const std::string &>(g.read("name"));
            return node;
        }
        static bool decode(const Node& node, Core::Group& g)
        {
            // Check if node is the right mask for class Group
            if (!node.IsMap()) return false;
            //if (!node.size() == 3) return false;
            g.update("name", node["name"].as<std::string>());
            return true;
        }
    };

   /*-------------------------------------------------*/
  /*             Core::Event Convertations           */
 /*-------------------------------------------------*/
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
