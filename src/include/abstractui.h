#pragma once

#include <usersobject.h>
#include <storage.h>

namespace UI {

class AbstractUI {
private:
    Storage::AbstractStorage& storage_;
    std::vector<UsersObject const *> cache_;
protected:
    std::vector<UsersObject const *>& cache() { return cache_; }

    void search(std::vector<Storage::AbstractStorage::Argument const *>& parameters);

    template <class T>
    void create(const std::vector<const Storage::AbstractStorage::Argument>& parameters);

    void remove(UsersObject const * object);

public:

    AbstractUI (Storage::AbstractStorage& storage):
        storage_(storage) {}
};

};

