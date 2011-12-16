#pragma once

#include <vector>
#include <string>

#include <abstractstorage.h>
#include <abstractui.h>

#ifndef _BACKEND_CPP_
extern
#endif /* _ABSTRACT_BACKEND_CPP_ */
std::vector<class AbstractBackend *> backends;

class AbstractBackend {
public:
    enum Type {
        STORAGE,
        UI
    };

private:
    const Type type_;

public:
    AbstractBackend (const enum Type type):
        type_(type)
        {
            backends.push_back(this);
        }
    
    virtual void init(const std::vector<std::string>& args) = 0;
        /* Initilize required resources. Such as memory, shared objects,
         * create auxiliary objects, etc.
         */

    const Type type() const throw ()
        { return type_; }
};

class StorageBackend: public AbstractBackend, public Storage::AbstractStorage {
public:
    StorageBackend():
        AbstractBackend(AbstractBackend::STORAGE)
        {}
};

class UIBackend: public AbstractBackend, public UI::AbstractUI {
public:
    UIBackend():
        AbstractBackend(AbstractBackend::UI)
        {}
};

