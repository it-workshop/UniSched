#pragma once

#include <vector>
#include <string>

#include <iostream>

/** @class Module
 * @brief An abstract class for module.
 *
 * Every module must be an shared object which contains static objec of
 * class implementing this one.
 */
class Module {
public:
    /** @enum Type
     * @brief Provides module type identification without typeid operator.
     */
    enum Type {
/* TODO: uncomment it, when create database class. */
/*        STORAGE,*/
        UI
    };

private:
    const Type type_;
                        /**< Type of the module.
                         * @internal Use in the type() method and constructor
                         * only.
                         */
    const std::string name_;
                        /**< Name of the module.
                         * @internal Use in the name() method and constructor
                         * only.
                         */

public:
    Module (const enum Type type, const std::string& name);
                        /**< @brief Constructor.
                         * @param [in] type Type of the module.
                         * @param [in] name Name of the module.
                         * @internal use only in the classes implementing this 
                         * one.
                         */
    
    virtual void init(const std::vector<std::string>& args) = 0;
                        /**< @brief Initilize required resources. Such as memory,
                         * shared objects, create auxiliary objects, etc.
                         * @param [in] args Command line program arguments.
                         */

    const Type type() const throw ()
                        /**< @brief Get type of the module.
                         * @return Type identificator.
                         */
    {
        return type_;
    }

    const std::string& name() const throw()
                        /**< @brief Get name of the module.
                         * @return Name of the module.
                         */
    {
        return name_;
    }
};

/** @brief Get collection of loaded modules.
 * @return Vector with object of classes implementing Module class.
 */
std::vector<Module *>& modules();


