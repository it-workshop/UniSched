#pragma once

#include <object.h>
#include <string>
#include <utility>

namespace Core {

typedef std::pair<std::string,Object *> named_object;
typedef std::pair<named_object,named_object> Link;

Link make_link(const std::string& first_name, Object *first,
               const std::string& second_name, Object *second)
{
    return std::make_pair<named_object,named_object>(
        std::make_pair<std::string,Object *>(first_name, first),
        std::make_pair<std::string,Object *>(second_name, second));
}

}
