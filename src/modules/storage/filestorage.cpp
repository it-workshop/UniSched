#include "filestorage.hpp"    

#include <yaml-cpp/yaml.h>
    
FileStorage::FileStorage(std::vector<Module *>* modules, void *handle):
        AbstractStorage("FileStorage", DATABASE_YAML, modules, handle)
{
    std::cout << "(FileStorage Interface constructor) ";
}
   
void FileStorage::push(const Core::objid_t id, const std::string& name, const boost::any& value)
{
    std::cout << ">>> FileStorage: Property pushed." << std::endl;
}

void FileStorage::connect()
{
    std::cout << ">>> FileStorage: Module connected. Ready for service.\n"
              << ">>> FileStorage: Using database: " << dbase_fname() << std::endl;
    load(dbase_fname());
}

void FileStorage::disconnect()
{
    //dump("brand_new_database.yaml");
    dump(dbase_fname());
    std::cout << "<<< FileStorage: Module disconnected. Bye bye." << std::endl;
}

void FileStorage::create(const Core::Object *object)
{
    std::cout << ">>> FileStorage: Object created." << std::endl;
}

void FileStorage::remove(const Core::objid_t id)
{
    std::cout << ">>> FileStorage: Object removed." << std::endl;
}
    
void FileStorage::init (const std::vector<std::string>& args)
{
    std::cout << "FileStorage INIT" << std::endl;
}

void FileStorage::dump(const std::string& dbase_fname)
{
    YAML::Node out;
    
    for (auto iter : objects())
    {
        YAML::Node obj;
        obj["Object"] = iter.second->type();
        obj["ID"] = iter.first;
        
        switch (iter.second->type()) {
        case Core::PERSON:
            obj["VCard"] = *dynamic_cast<Core::Person *>(iter.second);
            
            obj["groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("groups"));
                
        break;
        case Core::GROUP:
            obj["VCard"] = *dynamic_cast<Core::Group *>(iter.second);
            
            obj["people"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("people"));
            
            obj["parent_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("parent_groups"));
            
            obj["children_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("children_groups"));
            
        break;
        case Core::EVENT:
            obj["VCard"] = *dynamic_cast<Core::Event *>(iter.second);
            
            obj["people"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("people"));
            
            obj["children_groups"] = boost::any_cast<const std::vector<Core::Object *> &>
                (iter.second->read("children_groups"));
                
        break;
        default:
            obj["VCard"] = "No information";
        break;
        }
        
        out.push_back(obj); 
    }

    std::ofstream base(dbase_fname);

    base << out << std::endl;
    
    base.close();
}

inline void FileStorage::link(const std::map<Core::Object *, std::vector<Core::objid_t>>& connections)
{
    for (auto iter : connections)
    {
        for (auto jter : iter.second)
        {
            iter.first->connect( find_object(jter) );
        }
    }   
}

Core::Object * FileStorage::find_object(const Core::objid_t key_id)
{
    for (auto iter : objects())
    {
        if (iter.first == key_id) return iter.second;
    }
    return nullptr;
}

bool FileStorage::load(const std::string& dbase_fname)
{
    YAML::Node in = YAML::LoadFile(dbase_fname);
    
    std::map<Core::Object *, std::vector<Core::objid_t>> links_person,
                                                         links_group,
                                                         links_event;

    for (auto iter = in.begin(); iter != in.end(); iter ++)
    {
        auto type = (*iter)["Object"].as<Core::obj_t>();
        auto id = (*iter)["ID"].as<Core::objid_t>();        
        auto vcard = (*iter)["VCard"].as<std::map<std::string, boost::any>>();
        
        Core::Object *new_object;
        
        switch (type) {
        case Core::PERSON:
            new_object = create_in_memory<Core::Person>(id);
            new_object->update(vcard);
            for (auto jter  = (*iter)["groups"].begin();
                      jter != (*iter)["groups"].end(); jter ++)
            {
                 links_person[new_object].push_back( jter->as<Core::objid_t>() );
            }
        break;
        case Core::GROUP:
            new_object = create_in_memory<Core::Group>(id);
            new_object->update(vcard);
            for (auto jter  = (*iter)["children_groups"].begin();
                      jter != (*iter)["children_groups"].end(); jter ++)
            {
                 links_group[new_object].push_back( jter->as<Core::objid_t>() );
            }
        break;
        case Core::EVENT:
            new_object = create_in_memory<Core::Event>(id);
            new_object->update(vcard);
            for (auto jter  = (*iter)["children_groups"].begin();
                      jter != (*iter)["children_groups"].end(); jter ++)
            {
                 links_event[new_object].push_back( jter->as<Core::objid_t>() );
            }
        break;
        default:
            return false;
        break;
        }
    }
    
    try {
        link(links_person);
        link(links_group);
        link(links_event);
    }
    catch (int e)
    {
    }

    return true;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new FileStorage(modules, handle);
}

};

