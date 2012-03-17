#pragma once

#include <module.h>
#include <abstractui.h>

namespace Core {

class AbstractStorage : public Module {
private:
    AbstractUI *ui_;
    const std::string dbase_fname_;
    
protected:
    const std::string& dbase_fname() { return dbase_fname_; }

    AbstractUI * ui() { return ui_; }
    
    std::map<objid_t, Object *>& objects() { return ui_->objects_; }
    
    static const obj_t object_type(const Object *object) { return object->type(); }

    const std::map<objid_t, Object *>& objects() const { return ui_->objects(); }
    
    template <typename T>
    Object * create_in_memory(const objid_t id) { return ui_->create<T>(id); }

public:
    AbstractStorage(const std::string name, const std::string dbase_fname,
        std::vector<Module *>* modules, void *handle):
        Module(Module::STORAGE, name, modules, handle),
        dbase_fname_ (dbase_fname)
    {}

    void set_UI(AbstractUI* ui)
    {
        ui_ = ui;
        ui->set_storage(this);
    }

    virtual void push(const objid_t id, const std::string& name, const boost::any& value) = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void create(const Object *object) = 0;
    virtual void remove(const objid_t id) = 0;
    virtual void dump() = 0; // Ok, You probably don't need 
                             // this for the SQLite DB, but
    virtual bool load() = 0; // it could be useful to make a 
                             // somewhat DB-backup-method for
                             // emergancy cases (in the future).
};

}

