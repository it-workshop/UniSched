#pragma once

#include <module.h>
#include <abstractui.h>

namespace Core {

class Algorithm : public Module {
private:
    AbstractUI *ui_;
protected:
public:
    Algorithm(const std::string name, std::vector<Module *>* modules, void *handle):
        Module(Module::ALGORITHM, name, modules, handle), ui_(nullptr)
    {}

    void set_ui(AbstractUI* ui)
    {
        ui_ = ui;
    }

    AbstractUI * ui()
    {
        return ui_;
    }

    virtual void exec(Object * object = nullptr) = 0;
};

};

