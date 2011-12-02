#include <person.h>

using namespace Core;

void Person::del_group (AbstractGroup const * group)
{
    for (std::vector<AbstractGroup const *>::iterator it = groups_.begin(); it != groups_.end(); it++)
    {
        if (*it == group)
        {
            groups_.erase(it);
            break;
        }
    }
}

