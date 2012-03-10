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
            obj["VCard"] = "No information";
        break;
        }
        out.push_back(obj);
    }

    std::ofstream base(base_fname);

    base << out.as<std::string>();
    
    base.close();
}

bool AbstractUI::load(const std::string& base_fname)
{
    YAML::Node in = YAML::LoadFile(base_fname);

    for (YAML::const_iterator iter = in.begin(); iter != in.end(); iter ++)
    {
        const obj_t type = (*iter)["Object"].as<obj_t>();
        const objid_t id = (*iter)["ID"].as<objid_t>();
        const std::map<const std::string, boost::any> vcard =
            (*iter)["VCard"].as<std::map<const std::string, boost::any>>();
        switch (type) {
        case PERSON:
            add_object<Person>(id, vcard);
        break;
        case GROUP:
            add_object<Group>(id, vcard);
        break;
        case EVENT:
            add_object<Event>(id, vcard);
        break;
        default:
            return false;
        break;
        }
    }
}

template <typename T>
void AbstractUI::add_object(objid_t id, const std::map<const std::string, boost::any>& fields)
{
    Object *new_obj = new T(id, *this);
    for (auto iter = fields.begin(); iter != fields.end(); iter ++)
    {
        new_obj->update(iter->first, iter->second);
    }
    objects_[id] = new_obj;
}

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

void AbstractUI::search(const std::vector<std::pair<std::string, boost::any>>& parameters)
{
    std::vector<Object *> results;
    bool append = true;

    for (std::pair<std::string, boost::any> parameter: parameters)
    {
        if (append)
        {
            for (std::pair<const int, Object *> obj : objects_)
            {
                try
                {
                    if (parameter.second == obj.second->read(parameter.first))
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
                if (parameter.second == (*it)->read(parameter.first))
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

