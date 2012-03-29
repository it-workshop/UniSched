#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME L"TESTINGUI_SET_UNDEFINED_FIELD_WRONG"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    assert(object);

    object->update(L"Job", std::wstring(L"slave"));
    std::wcout << object->read(L"Job").type().name() << std::endl;
    try
    {
        object->update(L"Job", time_t(0));
        std::wcout << object->read(L"Job").type().name() << std::endl;
    }
    catch (boost::bad_any_cast& e)
    {
        std::wcout << L"Exception is catched :) L" << e.what() << std::endl;
        return 0;
    }

    std::wcout << L"Exception is not catched." << std::endl;

    return 1;
}

