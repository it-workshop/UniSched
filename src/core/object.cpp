#include <object.h>

using namespace Core;

const Field& Object::pull(const std::string& name) const
{
    return ui_.pull(name);
}

void Object::push(const Field& field)
{
    return ui_.push(id(), field);
}

