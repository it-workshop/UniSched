#include <manager.h>
#include <yaml-cpp/yaml.h>

using namespace Core;

Manager::Manager(std::fstream input_storage)
{
    YAML::Parser parser(input_storage);
    YAML::Node doc;
    parser.GetNextDocument(doc);
    for (int i = 0; i < doc.size(); i ++)
    {
        int old_id;
        doc[i]["ID"] >> old_id;
        //...
    }
}

const Field& Manager::pull(const std::string& name) const throw (std::bad_cast)
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

std::vector<Object *>&
Manager::search(const std::vector<const Field *>& parameters) const
{
    static std::vector<Object *> results;

    results.clear();

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

    return results;
}


