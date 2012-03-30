#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_SET_DEFINED_FIELD_RIGHT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    object->update("name", std::string("John"));
    object->update("surname", std::string("Connor"));
    object->update("sex", std::string("MALE"));

    return 0;
}

