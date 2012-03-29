#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME L"TESTINGUI_SET_UNDEFINED_FIELD_RIGHT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    object->update(L"Job", std::wstring(L"slave"));
    std::wcout << L"Job: " << boost::any_cast<std::wstring>(object->read(L"Job")) << std::endl;
    object->update(L"Job", std::wstring(L"master"));
    std::wcout << L"Job: " << boost::any_cast<std::wstring>(object->read(L"Job")) << std::endl;

    return boost::any_cast<std::wstring>(object->read(L"Job")) != L"master";
}

