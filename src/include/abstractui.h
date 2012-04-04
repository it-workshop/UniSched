#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <typeinfo>
#include <iostream>

#include <object.h>
#include <module.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

/** @namespace Core
 * @brief UserInterface Objects.
 */
namespace Core {

/** @class AbstractUI
 * @brief Interface for frontend modules.
 */
class AbstractUI: public Module {
friend class Object;
friend class AbstractStorage;

private:
    std::map<objid_t, Object *> objects_;
                        /**< Model objects. Each object must be saved here for
                         * correct work of storage.
                         *
                         * @intertal You must use this only with object(),
                         * set_object() and new_id() mehods, you can redefine
                         * this methods but do not use this field in other code.
                         */
    std::vector<Object *> cache_;
                        /**< Search cache. */
    int new_id_;
    const int new_id()
    {
        return new_id_++;
    }
                        /**< @brief Return new object identificator and reserve
                         * cell for it in the objects vector.
                         * @return New id.
                         *
                         * @intertal Do not use this method anywhere, it used by
                         * create method.
                         */

    Object * set_object(Object * object)
                        /**< @brief Apply changes in an object.
                         * @param [in] object Object to apply.
                         */
    {
        return objects_[object->id()] = object;
    }

    class AbstractStorage *storage_;

    void create_in_storage(const Object *object);
    lua_State *vm_;

    static int _lua___cache___index(lua_State *state);
    static int _lua___cache___newindex(lua_State *state);
    static int _lua___cache___len(lua_State *state);
    static int _lua___cache___next(lua_State *state);
    static int _lua___cache___ipairs(lua_State *state);

    static int _lua___object___index(lua_State *state);
    static int _lua___object___newindex(lua_State *state);
    static int _lua___object___eq(lua_State *state);
    static int _lua_object_type(lua_State *state);
    static int _lua_object_read(lua_State *state);
    static int _lua_object_update(lua_State *state);
    static int _lua_object_connect(lua_State *state);
    static int _lua_object_disconnect(lua_State *state);

    static int _lua_create(lua_State *state);
    static int _lua_search(lua_State *state);
    static int _lua_remove(lua_State *state);

    static void _lua_create_lua_object(lua_State *state, Core::Object *);

protected:
    void push(const int id, const std::string& name, const boost::any& value);
                        /**< @brief Save @a field of object with @a id it hte
                         * database
                         * @param [in] id Identificator of the object.
                         * @param [in] name Name of the field to be saved.
                         * @param [in] value Value of the field to be saved.
                         */
    void push(Object *object, Object *with, bool connect);

    void remove(Object * object);
                        /**< @brief Remove object from the storage.
                         * @param [in] object Object to delete.
                         */

    template <class T>
    Object * create(const objid_t new_id)
                        /**< @brief Create an object of the T type with given id.
                         * This method is designed to be used only in the 
                         * AbstractStorage class.
                         * @param [in] id Identificator of the new object.
                         * @param [in] parameters new object`s data.
                         */
    {
        if ( objects_.count(new_id) ) return nullptr;
        cache_.push_back(set_object(new T(new_id, *this)));
        create_in_storage(cache_.back());
        if (new_id_ <= new_id) { new_id_ = new_id + 1; }
        return cache_.back();
    }

    std::vector<Object*> search(const std::map<std::string, boost::any>& parameters = std::map<std::string, boost::any>());
                        /**< @brief Search objects by some parameters.
                         * @param [in] parameters Search parameters.
                         *
                         * Parameters are connected by logical AND.
                         * If parameter have not got a name, search value
                         * by the any field of specified type. If value
                         * is empty that all objects will satisfied.
                         */

    const std::map<objid_t, Object *>& objects() const
    {
        return objects_;
    }
    
    std::vector<Object *>& cache()
                        /**< @brief Get search cache.
                         * @return Search cache.
                         * @internal For this and inherited classes only.
                         */
    {
        return cache_;
    }

    void reset_cache() throw ()
                        /**< @brief Clears search cache.
                         * @internal For this and inherited classes only.
                         *
                         * Delete all information about objects from the cache.
                         */
    {
        cache_.clear();
    }

    void set_storage(class AbstractStorage *storage)
    {
        storage_ = storage;
    }

    bool exec_algorithm(const std::string& name, Object *object = nullptr)
    {
        lua_getglobal(vm_, "algorithms");
        lua_getfield(vm_, -1, name.c_str());
        if (lua_isnil(vm_, -1))
        {
            lua_pop(vm_, 2);
            return false;
        }
        _lua_create_lua_object(vm_, object);
        if (lua_pcall(vm_, 1, 0, 0))
        {
            std::cerr << lua_tostring(vm_, -1) << std::endl;
            lua_pop(vm_, 2);
            return false;
        }
        lua_pop(vm_, 1);
        return true;
    }

    lua_State *vm()
    {
        return vm_;
    }

public:
    AbstractUI (const std::string& name, std::vector<Module *>* modules,
            void *handle):
        Module(Module::UI, name, modules, handle), new_id_(0), storage_(nullptr)
                        /**< @brief constructor.
                         * @param name Name of the frontend.
                         */
    {}

    ~AbstractUI ()
    {
        for (auto object : objects_)
        {
            delete object.second;
        }
    }

    template <class T>
    Object * create()
                        /**< @brief Create an object of the T type.
                         * @param [in] parameters new object`s data.
                         */
    {
        cache_.push_back(set_object(new T(new_id(), *this)));
        create_in_storage(cache_.back());
        return cache_.back();
    }

    virtual int run() = 0;
                        /**< @brief Main method of frontend class. It is called
                         * from main.
                         * @return Program return code.
                         */

    Object * object(const int id) const throw (std::bad_cast)
                        /**< @brief Return object by id.
                         * @param [in] id Object identificator.
                         * @return Requested object.
                         *
                         * Use this method carefully. It can be moved to the
                         * protected or private section in the future.
                         */
    {                    
        return objects_.at(id);
    }
    void init_algorithms();
    void deinit_algorithms();
};

};

#include <abstractstorage.h>
