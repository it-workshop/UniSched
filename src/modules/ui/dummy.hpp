#include <iostream>

#include <boost/format.hpp>

#include <abstractui.h>
#include <group.h>
#include <person.h>

#include "paths.hpp"


class DummyInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    void test_person();
    void test_group();
    void show_objects();
    void yaml_load_dump();
    DummyInterface(std::vector<Module *>* module, void *handle);
};

