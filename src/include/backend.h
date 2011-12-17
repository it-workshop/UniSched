#pragma once

#include <vector>
#include <string>

#ifndef _BACKEND_CPP_
extern
#endif /* _BACKEND_CPP_ */
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

