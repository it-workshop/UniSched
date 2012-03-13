#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_SET_UNDEFINED_FIELD_RIGHT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    object->update("Job", std::string("slave"));
    std::cout << "Job: " << boost::any_cast<std::string>(object->read("Job")) << std::endl;
    object->update("Job", std::string("master"));
    std::cout << "Job: " << boost::any_cast<std::string>(object->read("Job")) << std::endl;

    return boost::any_cast<std::string>(object->read("Job")) != "master";
}

