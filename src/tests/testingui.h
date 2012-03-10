#include <abstractui.h>

class TestingUI : public Core::AbstractUI {

public:
    TestingUI(std::vector<Core::Module *>* modules, void *handle):
        AbstractUI(TESTINGUI_NAME, modules, handle)
    {}

    void init(const std::vector<std::string>& args)
    {}

    int run();
};

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new TestingUI(modules, handle);
}

};

