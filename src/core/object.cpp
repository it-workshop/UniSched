#include <object.h>

using namespace Core;

const Field& Object::pull(const std::string& name) const
{
    return manager_.pull(name);
}

void Object::push(const Field& field)
{
    return manager_.push(id(), field);
}

