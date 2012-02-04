#pragma once

#include <vector>
#include <string>

#include <iostream>


class AbstractBackend {
public:
    enum Type {
        STORAGE,
        UI
    };

private:
    const Type type_;

public:
    AbstractBackend (const enum Type type);
    
    virtual void init(const std::vector<std::string>& args) = 0;
        /* Initilize required resources. Such as memory, shared objects,
         * create auxiliary objects, etc.
         */

    const Type type() const throw ()
        { return type_; }
};

std::vector<AbstractBackend *>& backends();

