/** @file
 * @brief Core::object implementation.
 * @author Derbenev Aleksander
 * @author Mosyagin Igor
 * @date 2012
 */

#include <object.h>

using namespace Core;

void Object::update(const std::string& name, const boost::any& value)
    throw (boost::bad_any_cast)
{
    check_field(name, value);
    if (!fields_[name].empty() && fields_[name].type() != value.type())
    {
        throw boost::bad_any_cast();
    }
    fields_[name] = value;
    ui_.push(id(), name, value);
}

void Object::update(const std::map<std::string, boost::any>& fields)
    throw (boost::bad_any_cast)
{
    for (auto f: fields) {
        this->update(f.first, f.second);
    }
}

void Object::update(const std::string& name, Object *object, const bool connect)
    throw (boost::bad_any_cast)
{
    if (fields_[name].empty())
    {
        if (!connect)
        {
            return;
        }
        std::vector<Object *> vector;
        fields_[name] = vector;
    }
    auto& vector = boost::any_cast<std::vector<Object *>&>(fields_[name]);
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
    }
    else
    {
        for (auto it = vector.begin(); it != vector.end(); it++)
        {
            if (*it == object)
            {
                vector.erase(it);
                return;
            }
        }
    }
    ui_.push(this, object, connect);
}

void Object::back_update(const std::string& name, Object *object, const bool connect)
    throw (boost::bad_any_cast)
{
    if (fields_[name].empty())
    {
        if (!connect)
        {
            return;
        }
        std::vector<Object *> vector;
        vector.push_back(object);
        fields_[name] = vector;
        return;
    }
    auto& vector = boost::any_cast<std::vector<Object *>&>(fields_[name]);
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


void Object::back_connect(Object * object, const bool connect)
        throw (std::bad_cast)
{
    back_update(back_link_field(object), object, connect);
}

void Object::connect(Object * object, const bool connect)
        throw (std::bad_cast)
{
    update(link_field(object), object, connect);
    object->back_connect(this, connect);
}

void Object::disconnect(Object *object) throw (std::bad_cast)
{
    connect(object, false);
}

void Object::cleanup()
{
    for (auto& field : fields_)
    {
        if (typeid(std::vector<Object *>) != field.second.type())
        {
            continue;
        }
        auto& vector = boost::any_cast<std::vector<Object *>&>(field.second);
        if (disconnect_way(field.first))
        {
            for (auto& object : vector)
            {
                disconnect(object);
            }
            continue;
        }
        for (auto& object : vector)
        {
            object->disconnect(this);
        }
    }
}

