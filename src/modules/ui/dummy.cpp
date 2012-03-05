#include <abstractui.h>

#include <iostream>

class DummyInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    DummyInterface(std::vector<Module *>* module, void *handle);
};

void DummyInterface::init(const std::vector<std::string>& args)
{
    std::cout << "Dummy Interface INIT" << std::endl;
}

DummyInterface::DummyInterface(std::vector<Module *>* modules, void *handle):
    AbstractUI("DummyUI", modules, handle)
{
    std::cout << "Hello constructor!" << std::endl;
}

int DummyInterface::run()
{
    std::cout << "Dummy Interface RUN" << std::endl;
    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

