/** @file
 * @brief Definition of the AbstractUI class.
 * @author Aleksander Derbenev
 * @author Arshavir Ter-Gabrielyan
 * @author Igor Mosyagin
 * @date 2011-2012
 */
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
 * @brief Core Objects.
 */
namespace Core {

/** @class AbstractUI
 * @brief Interface for frontend modules.
 *
 * Fabric of objects.
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
    {
        return objects_[object->id()] = object;
    }
                        /**< @brief Apply changes in an object.
                         * @param [in] object Object to apply.
                         * @return Object, that was an argument.
                         */

    class AbstractStorage *storage_;
                        /**< Storage of objects.
                         */

    void create_in_storage(const Object *object);
                        /**< Create object in the storage.
                         * @param [in] object Object to save into storage.
                         */
    lua_State *vm_;
                        /**< Lua virtual machine instance.
                         */

    static int _lua___object___index(lua_State *state);
                        /**< Lua binding for object [] read operator.
                         * @param [in] state Lua vm state.
                         *
                         * calls _lua_object_read()
                         */
    static int _lua___object___newindex(lua_State *state);
                        /**< Lua binding for object [] write operator.
                         * @param [in] state Lua vm state.
                         *
                         * calls _lua_object_update()
                         */
    static int _lua___object___eq(lua_State *state);
                        /**< Lua binding for objct == operator.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_type(lua_State *state);
                        /**< Lua binding for object.type() method.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_id(lua_State *state);
                        /**< Lua binding for object.id() method.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_read(lua_State *state);
                        /**< Lua binding for object.read() method.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_update(lua_State *state);
                        /**< Lua binding for object.update() method.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_connect(lua_State *state);
                        /**< Lua binding for object.connect() method.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_object_disconnect(lua_State *state);
                        /**< Lua binding for object.disconnect() method.
                         * @param [in] state Lua vm state.
                         */

    static int _lua_create(lua_State *state);
                        /**< Lua binding for create() function.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_get_object(lua_State *state);
                        /**< Lua binding for get_object() function.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_search(lua_State *state);
                        /**< Lua binding for search() function.
                         * @param [in] state Lua vm state.
                         */
    static int _lua_remove(lua_State *state);
                        /**< Lua binding for remove() function.
                         * @param [in] state Lua vm state.
                         */


protected:
    static void lua_create_lua_object(lua_State *state, Core::Object *);
    void push(const int id, const std::string& name, const boost::any& value);
                        /**< @brief Save @a field of object with @a id it hte
                         * database
                         * @param [in] id Identificator of the object.
                         * @param [in] name Name of the field to be saved.
                         * @param [in] value Value of the field to be saved.
                         */
    void push(Object *object, Object *with, bool connect);
                        /**< Save connection state into the storage.
                         * @param [in] object The object that connect.
                         * @param [in] with The object to connect with.
                         * @param [in] connect State of connection (true if
                         * connect).
                         */

    void remove(Object * object);
                        /**< @brief Remove object from the storage.
                         * @param [in] object Object to delete.
                         */

    template <class T>
    Object * create(const objid_t new_id)
    {
        if ( objects_.count(new_id) ) return nullptr;
        Object *object = set_object(new T(new_id, *this));
        create_in_storage(object);
        if (new_id_ <= new_id) { new_id_ = new_id + 1; }
        return object;
    }
                        /**< @brief Create an object of the T type with given id.
                         * This method is designed to be used only in the 
                         * AbstractStorage class.
                         * @param [in] id Identificator of the new object.
                         * @return Object that was created.
                         */

    std::vector<Object*>
    search(const std::map<std::string,
            boost::any>& parameters = std::map<std::string, boost::any>());
                        /**< @brief Search objects by some parameters.
                         * @param [in] parameters Search parameters.
                         * @return Objects that were found.
                         *
                         * Parameters are connected by logical AND.
                         * If parameter have not got a name, search value
                         * by the any field of specified type. If value
                         * is empty that all objects will satisfied.
                         */

    std::vector<Object*> search(const std::string query);
                        /**< Search objects by string fields.
                         * @param [in] query String to search.
                         * @return Objects that were found.
                         */

    const std::map<objid_t, Object *>& objects() const
    {
        return objects_;
    }
                        /**< Get all objects.
                         * @return Map of objects.
                         */
    
    void set_storage(class AbstractStorage *storage)
    {
        storage_ = storage;
    }
                        /**< Set storage. Called, when storage is selected.
                         * @param [in] The storage that was selected.
                         */

    lua_State *vm()
    {
        return vm_;
    }
                        /**< Getter for lua vm.
                         * @return Lua virtual machine.
                         */

public:
    AbstractUI (const std::string& name, std::vector<Module *>* modules,
            void *handle):
        Module(Module::UI, name, modules, handle), new_id_(0), storage_(nullptr)
                        /**< @brief constructor.
                         * @param [in] name Name of the frontend.
                         * @param [in] modules Vector for all modules.
                         * @param [in] handle Handle of the shared object.
                         */
    {}

    ~AbstractUI ()
    {
        for (auto object : objects_)
        {
            delete object.second;
        }
    }
                        /**< Destructor.
                         *
                         * Deletes all objects, but not from database.
                         */

    template <class T>
    Object * create()
    {
        Object *object = set_object(new T(new_id(), *this));
        create_in_storage(object);
        return object;
    }
                        /**< @brief Create an object of the T type.
                         * @return Object that was created.
                         */

    virtual void init(Config& conf, const std::vector<std::string> args);
                        /**< Configure module.
                         * @param [in] conf Configuration.
                         * @param [in] args Command line arguments.
                         * It's called when this module is selected as ui.
                         */

    virtual int run() = 0;
                        /**< @brief Main method of frontend class. It is called
                         * from main.
                         * @return Program return code.
                         * Must be implemented in the children classes.
                         */

    Object * object(const int id) const throw (std::bad_cast)
    {                    
        return objects_.at(id);
    }
                        /**< @brief Return object by id.
                         * @param [in] id Object identificator.
                         * @return Requested object.
                         *
                         * @attention Use this method carefully. It can be
                         * moved to the protected or private section in the
                         * future.
                         */
 
    void init_algorithms();
                        /**< Load scripts.
                         */
    void deinit_algorithms();
                        /**< Stop lua vm.
                         *
                         * FIXME: Is there is OK that vm created in the
                         * Config class but stopped here?
                         */
};

};

#include <abstractstorage.h>
