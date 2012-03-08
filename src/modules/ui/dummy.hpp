#include <iostream>

#include <abstractui.h>
#include <group.h>
#include <person.h>


class DummyInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    void test_person();
    void test_group();
    DummyInterface(std::vector<Module *>* module, void *handle);
};

