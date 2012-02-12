#include <abstractui.h>

using namespace UI;

template <class T>
void AbstractUI::create(const std::vector<const Core::Manager::Argument>& parameters)
{
    cache_.clear();

    cache_.push_back(dynamic_cast<UsersObject *&>(manager_->create<T>(parameters)));
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

    manager_->remove(dynamic_cast<Core::ManagersObject *>(object));
}

void AbstractUI::search(std::vector<Core::Manager::Argument *>& parameters)
{
    cache_.clear();

    {
        std::vector<Core::ManagersObject *> *temp_cast_vector = manager_->search(parameters);

        for (std::vector<Core::ManagersObject *>::iterator it = temp_cast_vector->begin(); it != temp_cast_vector->end(); it++)
        {
            cache_.push_back(dynamic_cast<UsersObject *>(*it));
        }

        delete[] temp_cast_vector;
    }
}

