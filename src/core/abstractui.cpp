#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

#ifdef WITH_YAML
#include <yaml-cpp/yaml.h>
#include <yaml.h>
#endif

using namespace Core;

#ifdef WITH_YAML

void AbstractUI::dump(const std::string& base_fname) const
{
    YAML::Node out;
    
    for (auto iter : objects_)
    {
        YAML::Node obj;
        obj["Object"] = iter.second->type();
        obj["ID"] = iter.first;
        
        switch (iter.second->type()) {
        case PERSON:
            obj["VCard"] = *dynamic_cast<Person *>(iter.second);
            
            obj["Groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("groups"));
                
        break;
        case GROUP:
            obj["VCard"] = *dynamic_cast<Group *>(iter.second);
            
            obj["Links"]["people"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("people"));
            
            obj["Links"]["parent_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("parent_groups"));
            
            obj["Links"]["children_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("children_groups"));
            
        break;
        case EVENT:
            obj["VCard"] = *dynamic_cast<Event *>(iter.second);
            
            obj["Links"]["people"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("people"));
            
            obj["Links"]["children_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("children_groups"));
                
        break;
        default:
            obj["VCard"] = "No information";
            obj["Links"] = "No links";
        break;
        }
        
        out.push_back(obj); 
    }

    std::ofstream base(base_fname);

    base << out << std::endl;
    
    base.close();
}

bool AbstractUI::load(const std::string& base_fname)
{
    bool result = true;

    YAML::Node in = YAML::LoadFile(base_fname);
    
    std::map<const objid_t, std::vector<objid_t>> links_person,
                                                  links_group,
                                                  links_event;

    for (auto iter = in.begin(); iter != in.end(); iter ++)
    {
        auto type = (*iter)["Object"].as<obj_t>();
        auto id = (*iter)["ID"].as<objid_t>();        
        auto vcard = (*iter)["VCard"].as<std::map<const std::string, boost::any>>();
        
        switch (type) {
        case PERSON:
            add_object<Person>(id, vcard);
            for (auto jter  = (*iter)["Groups"].begin();
                      jter != (*iter)["Groups"].end(); jter ++)
            {
                 links_person[id].push_back( jter->as<Core::objid_t>() );
            }
        break;
        case GROUP:
            add_object<Group>(id, vcard);
            for (auto jter  = (*iter)["Links"]["children_groups"].begin();
                      jter != (*iter)["Links"]["children_groups"].end(); jter ++)
            {
                 links_group[id].push_back( jter->as<Core::objid_t>() );
            }
        break;
        case EVENT:
            add_object<Event>(id, vcard);
            for (auto jter  = (*iter)["Links"]["children_groups"].begin();
                      jter != (*iter)["Links"]["children_groups"].end(); jter ++)
            {
                 links_event[id].push_back( jter->as<Core::objid_t>() );
            }
        break;
        default:
            result = false;
        break;
        }
    }
    
    link(links_person);
    link(links_group);
    link(links_event);    

    return result;
}

inline void AbstractUI::link(const std::map<const objid_t, std::vector<objid_t>> connections)
{
    for (auto iter : connections)
    {
        for (auto jter : iter.second)
        {
            objects_[iter.first]->connect( objects_[jter] );
        }
    }   
}

/* Template method in the .cpp? No way if it is not internal. Be careful. */
template <typename T>
void AbstractUI::add_object(objid_t id, const std::map<const std::string, boost::any>& fields)
{
    Object *new_obj = new T(id, *this);
    
    for (auto iter : fields)
    {
        new_obj->update(iter.first, iter.second);
    }
    objects_[id] = new_obj;
}

#endif /* WITH_YAML */

static const bool operator==(const boost::any& lhs, const boost::any& rhs)
    throw (boost::bad_any_cast)
{
    if (lhs.empty() != rhs.empty())
    {
        return false;
    }
    if (typeid(std::string) == lhs.type())
    {
        return boost::any_cast<std::string>(lhs)
            == boost::any_cast<std::string>(rhs);
    }
    if (typeid(time_t) == lhs.type())
    {
        return boost::any_cast<time_t>(lhs)
            == boost::any_cast<time_t>(rhs);
    }
    throw boost::bad_any_cast();
}

std::vector<Object *> AbstractUI::search(const std::map<std::string, boost::any>& parameters)
{
    std::vector<Object *> results;
    for (auto m: objects_) {
        results.push_back(m.second);
    }
    for (auto p: parameters)
    {
        for (auto it = results.begin(); it != results.end(); it++)
        {
            try
            {
                if (p.second == (*it)->read(p.first))
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

    return results;
}

void AbstractUI::push(const int id, const std::string& name,
        const boost::any& value)
{
    if (storage_)
    {
        storage_->push(id, name, value);
    }
}

void AbstractUI::remove(Object *object)

{
    int id = object->id();
    objects_.erase(objects_.find(id));
    object->cleanup();
    delete object;
    if (storage_)
    {
        storage_->remove(id);
    }
    for (auto it = cache_.begin(); it != cache_.end(); it++)
    {
        if (*it == object)
        {
            cache_.erase(it);
            return;
        }
    }
}

void AbstractUI::create_in_storage(const Object *object)
{
    if (storage_)
    {
        storage_->create(object);
    }
}

