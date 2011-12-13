#pragma once

#include <usersobject.h>
#include <abstractstorage.h>

namespace UI {

class AbstractUI {
private:
    Storage::AbstractStorage *storage_;
    std::vector<UsersObject *> cache_;
protected:
    std::vector<UsersObject *>& cache() { return cache_; }

    void search(std::vector<Storage::AbstractStorage::Argument *>& parameters);

    template <class T>
    void create(const std::vector<const Storage::AbstractStorage::Argument>& parameters);

    void remove(UsersObject * object);

public:

    AbstractUI (Storage::AbstractStorage * storage):
        storage_(storage) {}

    AbstractUI ()
        {}

    void set_storage(Storage::AbstractStorage * storage)
        { storage_ = storage; }
};

};

