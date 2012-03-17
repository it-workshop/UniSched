#include <iostream>

#include <boost/format.hpp>

#include <abstractui.h>
#include <group.h>
#include <person.h>

#include "../paths.hpp"


class DummyInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    void test_person();
    void test_group();
    void test_connect();
    void show_objects();
    bool yaml_load();
    void yaml_dump();
    DummyInterface(std::vector<Module *>* module, void *handle);
};

