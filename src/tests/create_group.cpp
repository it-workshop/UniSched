#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <group.h>

#define TESTINGUI_NAME L"TESTINGUI_CREATE_GROUP"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Group>();

    assert(object);

    std::cout << typeid(object).name() << std::endl;

    return 0;
}

