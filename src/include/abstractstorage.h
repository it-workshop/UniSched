/** @file
 * @brief Definition of AbstractStroage class.
 * @author Derbenev Aleksander
 * @author Arshavir Ter-Gabrielyan
 * @date 2012
 */
#pragma once

#include <module.h>
#include <abstractui.h>

#include <iostream>

namespace Core {

/** @class AbstractStorage
 * @brief Abstract storage of data.
 *
 * Provides methods to load, and save
 * data into database or file (must be implemented in the children classes).
 *
 * Childrens of this class must be in the independent shared object, that
 * must contain init function that creates instance of the implementation
 * class.
 */
class AbstractStorage : public Module {
private:
    AbstractUI *ui_;
                            /**< UserInterface, Used because it's a fabric of
                             * objects. Must to be used while data loading.
                             */
protected:
    AbstractUI * ui()
    {
        return ui_;
    }
                            /**< Getter for private field. Must be used in
                             * children classes.
                             * @return Current user interface.
                             */
    
    std::map<objid_t, Object *>& objects()
    {
        return ui_->objects_;
    }
                            /**< Getter for objects map in the User interface.
                             * Used because it's private field but this class
                             * is a friend of AbstractUI.
                             * @return map of objects.
                             */
    
    static const obj_t object_type(const Object *object)
    {
        return object->type();
    }
                            /**< Get type of object.
                             * @param [in] object Object to identify.
                             * @return type of the object.
                             * @deprecated object.type() is a public method.
                             * FIXME: Delete this method.
                             */
    static const objid_t object_id(const Object *object)
    {
        return object->id();
    }
                            /**< Get id of object.
                             * @param [in] object Object to identify.
                             * @return type of the object.
                             * @deprecated object.id() is a public method.
                             * FIXME: Delete this method.
                             */

    const std::map<objid_t, Object *>& objects() const
    {
        return ui_->objects();
    }
                            /**< Synonym of the objects() but for
                             * const methods.
                             * @return map of objects.
                             * @copydoc objects()
                             * TODO: Why it's needed?
                             */
    
    template <typename T>
    Object * create_in_memory(const objid_t id) { return ui_->create<T>(id); }
                            /**< Create objects using user interface.
                             * @param [in] id Id of object.
                             * @return object that was created.
                             * @deprecated ui() getter is here,
                             * ui.create<T>(id) is public method.
                             * FIXME: Delete this method.
                             */

    void set_new_id(const objid_t id)
    {
        ui_->new_id_ = id;
    }
                            /**< Set id of next object in AbstractUI.
                             * @param [in] id Id to set.
                             *
                             * Is need because this class is a friend of ui.
                             */

public:
    AbstractStorage(const std::string name, std::vector<Module *>* modules,
            void *handle):
        Module(Module::STORAGE, name, modules, handle)
    {}
                            /**< Constructor.
                             * @param [in] name Name of the module.
                             * @param [in] modules Vector with all modules.
                             * @param [in] handle Handle of shared object.
                             */

    void set_UI(AbstractUI* ui)
    {
        ui_ = ui;
        ui->set_storage(this);
    }
                            /**< Set UI. This method is called from main(),
                             * when this module is selected as an storage.
                             * @param [in] ui User interface to set.
                             */

    virtual void push(const objid_t id, const std::string& name,
                    const boost::any& value) = 0;
                            /**< Save value of a field in the storage.
                             * @param [in] id Id of object.
                             * @param [in] name Name of the field.
                             * @param [in] value Value of the field.
                             *
                             * Must be implemented in the children class.
                             */
    virtual void push_connect(objid_t id, objid_t with, bool connect) = 0;
                            /**< Save connection between objects in the storage.
                             * @param [in] id Id of object.
                             * @param [in] with Object to connect with.
                             * @param [in] connect State of connection (true
                             * if connect).
                             *
                             * Must be implemented in the children class.
                             */
    virtual void connect() = 0;
                            /**< The start of storage communication is.
                             * Load data from the storage.
                             * Must be implemented in the children class.
                             */
    virtual void disconnect() = 0;
                            /**< The end of storage communication is.
                             * Save data into storage if not saved yet.
                             * Must be implemented in the children class.
                             */
    virtual void create(const Object *object) = 0;
                            /**< Create object in the database.
                             * @param [in] object Object that just created.
                             *
                             * Must be implemented in the children class.
                             * @attention This methods also calls while loading
                             * is pending. Prevent your storage module to create
                             * duplicate of object.
                             */
    virtual void remove(const objid_t id) = 0;
                            /**< Remove object from the database.
                             * @param [in] id Id of object to remove from storage.
                             */
};

}

