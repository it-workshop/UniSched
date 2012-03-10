#pragma once

#include <module.h>
#include <abstractui.h>

namespace Core {

class AbstractStorage : public Module {
private:
    AbstractUI *ui_;
protected:
    AbstractUI * ui()
    {
        return ui_;
    }

    std::map<objid_t, Object *>& objects()
    {
        return ui_->objects_;
    }

public:
    AbstractStorage(const std::string name, std::vector<Module *>* modules,
            void *handle):
        Module(Module::STORAGE, name, modules, handle)
    {}

    void set_UI(AbstractUI* ui)
    {
        ui_ = ui;
    }

    virtual void load() = 0;

    virtual void push(const std::string& name, const boost::any& value) = 0;

    virtual void save() = 0;
};

}
