#pragma once

#include <usersobject.h>
#include <storage.h>

namespace UserInterface {

class AbstractUserInterface {
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
    AbstractUserInterface (Storage::AbstractStorage& storage):
        storage_(storage) {}
};

};

