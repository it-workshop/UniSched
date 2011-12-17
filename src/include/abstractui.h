#pragma once

#include <usersobject.h>
#include <abstractstorage.h>

#include <backend.h>

namespace UI {

class AbstractUI: public AbstractBackend {
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
        AbstractBackend(AbstractBackend::UI), storage_(storage) {}

    AbstractUI ():
        AbstractBackend(AbstractBackend::UI)
        {}

    void set_storage(Storage::AbstractStorage * storage)
        { storage_ = storage; }
};

};

