#include <object.h>

using namespace Core;

void Object::update(const std::string& name, const boost::any& value)
{
    check_field(name, value);
    fields_[name] = value;
    ui_.push(id(), name, value);
}

void Object::update(const std::string& name, Object *object, const bool connect)
    throw (boost::bad_any_cast)
{
    if (fields_[name].empty())
    {
        fields_[name] = std::vector<Object *>();
    }
    auto vector = boost::any_cast<std::vector<Object *>&>(fields_[name]);
    if (connect)
    {
        for (auto &it : vector)
        {
            if (it == object)
            {
                return;
            }
        }
        vector.push_back(object);
        return;
    }
    for (auto it = vector.begin(); it != vector.end(); it++)
    {
        if (*it == object)
        {
            vector.erase(it);
            return;
        }
    }
}

