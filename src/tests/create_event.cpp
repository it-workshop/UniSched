#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <event.h>

#define TESTINGUI_NAME "TESTINGUI_CREATE_EVENT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Event>();

    assert(object);

    std::cout << typeid(object).name() << std::endl;

    return 0;
}

