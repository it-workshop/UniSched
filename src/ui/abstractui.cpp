#include <abstractui.h>

using namespace UI;

template <class T>
void AbstractUI::create(const std::vector<const Storage::AbstractStorage::Argument>& parameters)
{
    cache_.clear();

    cache_.push_back(dynamic_cast<UsersObject *&>(storage_.create<T>(parameters)));
}

void AbstractUI::remove(UsersObject * object)
{
    for (auto it = cache_.begin(); it != cache_.end(); it++)
    {
        if (*it == object)
        {
            cache_.erase(it);
            break;
        }
    }

    storage_.remove(dynamic_cast<Storage::StorableObject *>(object));
}

void AbstractUI::search(std::vector<Storage::AbstractStorage::Argument *>& parameters)
{
    cache_.clear();

    {
        std::vector<Storage::StorableObject *> temp_cast_vector = storage_.search(parameters);

        for (std::vector<Storage::StorableObject *>::iterator it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            cache_.push_back(dynamic_cast<UsersObject *>(*it));
        }
    }
}

