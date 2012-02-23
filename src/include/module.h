#pragma once

#include <vector>
#include <string>

#include <iostream>


class Module {
public:
    enum Type {
/*        STORAGE,*/
        UI
    };

private:
    const Type type_;
    const std::string name_;

public:
    Module (const enum Type type, const std::string& name);
    
    virtual void init(const std::vector<std::string>& args) = 0;
        /* Initilize required resources. Such as memory, shared objects,
         * create auxiliary objects, etc.
         */

    const Type type() const throw ()
    {
        return type_;
    }

    const std::string& name() const throw()
    {
        return name_;
    }
};

std::vector<Module *>& modules();

