#include <abstractui.h>

using namespace UI;

template <class T>
void AbstractUI::create(const std::vector<const Storage::AbstractStorage::Argument>& parameters)
{
    cache_.clear();

    cache_.push_back(dynamic_cast<UsersObject const *&>(storage_.create<T>(parameters)));
}

void AbstractUI::remove(UsersObject const * object)
{
    for (auto it = cache_.begin(); it != cache_.end(); it++)
    {
        if (*it == object)
        {
            cache_.erase(it);
            break;
        }
    }

    storage_.remove(dynamic_cast<Storage::StorableObject const *>(object));
}

void AbstractUI::search(std::vector<Storage::AbstractStorage::Argument const *>& parameters)
{
    cache_.clear();

    {
        std::vector<Storage::StorableObject const *> temp_cast_vector = storage_.search(parameters);

        for (std::vector<Storage::StorableObject const *>::iterator it = temp_cast_vector.begin(); it != temp_cast_vector.end(); it++)
        {
            cache_.push_back(dynamic_cast<UsersObject const *>(*it));
        }
    }
}

