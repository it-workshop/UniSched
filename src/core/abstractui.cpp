#include <abstractui.h>
#include <yaml-cpp/yaml.h>
#include <person.h>
#include <group.h>
#include <event.h>

using namespace Core;

void AbstractUI::dump(const std::string& base_fname) const
{
    YAML::Node out;
    
    for (std::map<objid_t, Object *>::const_iterator iter = objects_.begin();
         iter != objects_.end(); iter ++)
    {
        YAML::Node obj;
        obj["Object"] = iter->second->type();
        obj["ID"] = iter->first;
        // Just fuck-off, dude :)
        switch (iter->second->type()) {
        case PERSON:
            obj["VCard"] = *static_cast<Person *>(iter->second);
        break;
        case GROUP:
            obj["VCard"] = *static_cast<Group *>(iter->second);
        break;
        case EVENT:
            obj["VCard"] = *static_cast<Event *>(iter->second);
        break;
        default:
            obj["VCard"] = "Unknown";
        break;
        }
        out.push_back(obj);
    }

    std::ofstream base(base_fname);

    base << out.as<std::string>();
    
    base.close();
}

void AbstractUI::load(const std::string& base_fname)
{
    YAML::Node in = YAML::LoadFile(base_fname);

    for (YAML::const_iterator iter = in.begin(); iter != in.end(); iter ++)
    {
        const obj_t new_obj_type = (const obj_t) (*iter)["Object"].as<obj_t>();
        const objid_t new_obj_id = (const objid_t) (*iter)["ID"].as<objid_t>();
        
        switch (new_obj_type) {
        case PERSON:
            objects_[new_obj_id] = new Person(new_obj_id, *this);
//          objects_[new_obj_id] = (*iter)["VCard"].as<Person>();
        break;
        case GROUP:
        break;
        case EVENT:
        break;
        default:
        break;
        }
    }
}

const Field& AbstractUI::pull(const std::string& name) const throw (std::bad_cast)
{
    for (const Field* parameter: parameters_)
    {
        if (parameter->name() == name)
        {
            return *parameter;
        }
    }
    throw std::bad_cast();
}

void AbstractUI::search(const std::vector<const Field *>& parameters)
{
    std::vector<Object *> results;
    bool append = true;

    for (const Field * parameter: parameters)
    {
        if (append)
        {
            for (std::pair<const int, Object *> obj : objects_)
            {
                try
                {
                    if (*parameter == obj.second->read(parameter->name()))
                    {
                        results.push_back(obj.second);
                    }
                }
                catch (std::bad_cast) /* Object has not field with that
                                       * name, or it's type is not like
                                       * field.
                                       */
                {}
            }
            append = false;
            continue;
        }
        for (auto it = results.begin(); it != results.end(); it++)
        {
            try
            {
                if (*parameter == (*it)->read(parameter->name()))
                {
                    continue;
                }
            }
            catch (std::bad_cast)
            {}
            it = results.erase(it);
        }
    }

    for (Object * object: results)
    {
        cache_.push_back(object);
    }
}

