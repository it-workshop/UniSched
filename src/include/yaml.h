#ifdef WITH_YAML

#include <yaml-cpp/yaml.h>

#include <object.h>
#include <person.h>
#include <group.h>
#include <event.h>

namespace YAML {
   /*--------------------------------------------------*/
  /*                   Decoding YAML                  */
 /*--------------------------------------------------*/
    template<>
    struct convert<std::map<std::string, boost::any>> {        
        static bool decode(const Node& node, std::map<std::string, boost::any>& fields)
        {
            if (!node.IsMap()) return false;
            for (auto iter = node.begin(); iter != node.end(); iter ++)
            {                
                if (iter->second.IsSequence()) // is sequence
                {
                    //return false;
                }
                else // is scalar
                {
                    if (iter->first.as<std::string>() == "birthday" or
                        iter->first.as<std::string>() == "begin"    or
                        iter->first.as<std::string>() == "duration")
                         fields[iter->first.as<std::string>()] = iter->second.as<time_t>();
                    else fields[iter->first.as<std::string>()] = iter->second.as<std::string>();
                }
            }
            return true;
        }
    };
   /*--------------------------------------------------*/
  /*               General Convertations              */
 /*--------------------------------------------------*/
    template<>
    struct convert<std::vector<Core::Object *>> {
        static Node encode(const std::vector<Core::Object *>& vector)
        {
            Node node;
            for (auto iter : vector)
            {
                node.push_back( iter->id() );
            }
            return node;
        }
    };
 
    template<>
    struct convert<Core::obj_t> {
        static Node encode(const Core::obj_t& ot)
        {
            Node node;
            switch (ot) {
            case Core::PERSON: node = "Person";  return node;
            case Core::GROUP:  node = "Group";   return node;
            case Core::EVENT:  node = "Event";   return node;
            default:           node = "Unknown"; return node;
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
  /*              Encoding Core::Person              */
 /*-------------------------------------------------*/
    template<>
    struct convert<Core::Person> {
        static Node encode(const Core::Person& p)
        {
            Node node;
            
            try {
                node["name"]     = boost::any_cast<const std::string &>(p.read("name")); 
                node["surname"]  = boost::any_cast<const std::string &>(p.read("surname"));
                node["sex"]      = boost::any_cast<const std::string &>(p.read("sex"));
                node["birthday"] = boost::any_cast<const time_t &>     (p.read("birthday"));
            }
            catch(YAML::KeyNotFound& e) {
                std::cout << e.what() << "\n";
            }
            
            return node;
        }
    };

   /*-------------------------------------------------*/
  /*              Encoding Core::Group               */
 /*-------------------------------------------------*/
    template<>
    struct convert<Core::Group> {
        static Node encode(const Core::Group& g)
        {
            Node node;
            node["name"] = boost::any_cast<const std::string &>(g.read("name"));
            return node;
        }
    };

   /*-------------------------------------------------*/
  /*              Encoding Core::Event               */
 /*-------------------------------------------------*/
    template<>
    struct convert<Core::Event> {
        static Node encode(const Core::Event& ev)
        {
            Node node;
            node["name"]     = boost::any_cast<const std::string &>(ev.read("name"));
            node["begin"]    = boost::any_cast<const time_t &>     (ev.read("begin"));
            node["duration"] = boost::any_cast<const time_t &>     (ev.read("duration"));
            return node;
        }
    };
}

#endif /* WITH_YAML */
