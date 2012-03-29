#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME L"TESTINGUI_SET_DEFINED_FIELD_RIGHT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    object->update(L"name", std::wstring(L"John"));
    object->update(L"surname", std::wstring(L"Connor"));
    object->update(L"sex", std::wstring(L"MALE"));

    return 0;
}

