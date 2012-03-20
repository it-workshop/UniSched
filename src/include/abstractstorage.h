#pragma once

#include <module.h>
#include <abstractui.h>

namespace Core {

class AbstractStorage : public Module {
private:
    AbstractUI *ui_;
protected:
    AbstractUI * ui() { return ui_; }
    
    std::map<objid_t, Object *>& objects() { return ui_->objects_; }
    
    static const obj_t object_type(const Object *object) { return object->type(); }
    static const objid_t object_id(const Object *object) { return object->id(); }

    const std::map<objid_t, Object *>& objects() const { return ui_->objects(); }
    
    template <typename T>
    Object * create_in_memory(const objid_t id) { return ui_->create<T>(id); }

    void set_new_id(const objid_t id) {ui_->new_id_ = id;}

public:
    AbstractStorage(const std::string name, std::vector<Module *>* modules,
            void *handle):
        Module(Module::STORAGE, name, modules, handle)
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
};

}

