/** @file
 * @brief Module class definition.
 * @author Derbenev Aleksander
 * @date 2011-2012
 */
#pragma once

#include <vector>
#include <string>

#include <config.h>

namespace Core {

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
        STORAGE,
        UI,
        ALGORITHM
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
    void *handle_;
                        /**< Handle of the shared object.
                         */

public:
    Module (const enum Type type, const std::string& name,
            std::vector<Module *>* modules, void *handle);
                        /**< @brief Constructor.
                         * @param [in] type Type of the module.
                         * @param [in] name Name of the module.
                         * @param [in] modules Collection of modules.
                         * @param [in] handle Handle of the module.
                         * @internal use only in the classes implementing this 
                         * one.
                         */
    
    virtual void init(Config& conf, const std::vector<std::string>& args) = 0;
                        /**< @brief Initilize required resources. Such as memory,
                         * shared objects, create auxiliary objects, etc.
                         * @param [in] args Command line program arguments.
                         */

    const Type type() const throw ()
    {
        return type_;
    }
                        /**< @brief Get type of the module.
                         * @return Type identificator.
                         */

    const std::string& name() const throw()
    {
        return name_;
    }
                        /**< @brief Get name of the module.
                         * @return Name of the module.
                         */

    static void unload_modules();
                        /**< Close all shared objects. */
    static void load_modules(Config& conf);
                        /**< Load modules.
                         * @param [in] conf Configuration.
                         */
    static std::vector<Module *> * modules();
                        /**< Return vector vith all modules.
                         */
};

}

