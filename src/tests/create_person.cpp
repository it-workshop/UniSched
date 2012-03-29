#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME L"TESTINGUI_CREATE_PERSON"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    std::cout << typeid(object).name() << std::endl;

    return 0;
}

