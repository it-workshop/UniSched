#include <object.h>

using namespace Core;

void Object::update(const std::string& name, const boost::any& value)
{
    check_field(name, value);
    if (value.type() != typeid(std::pair<Object *,bool>))
    {
        fields_[name] = value;
        ui_.push(id(), name, value);
        return;
    }
    if (fields_[name].empty())
    {
        fields_[name] = std::vector<Object *>();
    }
    auto tmp_pair = boost::any_cast<std::pair<Object *,bool>>(value);
    auto tmp_vect = boost::any_cast<std::vector<Object *>>(fields_[name]);
    if (tmp_pair.second)
    {
        for (Object * obj : tmp_vect)
        {
            if (obj == tmp_pair.first)
            {
                return;
            }
        }
        tmp_vect.push_back(tmp_pair.first);
    }
    else
    {
        for (auto it = tmp_vect.begin(); it != tmp_vect.end(); it++)
        {
            if (*it == tmp_pair.first)
            {
                tmp_vect.erase(it);
                break;
            }
        }
    }
    ui_.push(id(), name, value);
}

