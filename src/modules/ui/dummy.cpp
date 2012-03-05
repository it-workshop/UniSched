#include <abstractui.h>

class DummyInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    DummyInterface();
};

void DummyInterface::init(const std::vector<std::string>& args)
{
    std::cout << "Dummy Interface INIT" << std::endl;
}

DummyInterface::DummyInterface() : AbstractUI("DummyUI") {
    std::cout << "Hello constructor!" << std::endl;
}

int DummyInterface::run()
{
    std::cout << "Dummy Interface RUN" << std::endl;
    return 0;
}

DummyInterface _object;
