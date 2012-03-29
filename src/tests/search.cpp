#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME L"TESTINGUI_SEARCH"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    object->update(L"name", std::wstring(L"John"));
    object->update(L"surname", std::wstring(L"Connor"));
    object->update(L"sex", std::wstring(L"MALE"));
    object->update(L"Job", std::wstring(L"none"));

    object = create<Core::Person>();
    object->update(L"name", std::wstring(L"Sarah"));
    object->update(L"surname", std::wstring(L"Connor"));
    object->update(L"sex", std::wstring(L"FEMALE"));
    object->update(L"Job", std::wstring(L"waiter"));
    
    object = create<Core::Person>();
    object->update(L"name", std::wstring(L"Steve"));
    object->update(L"surname", std::wstring(L"Jobs"));
    object->update(L"sex", std::wstring(L"MALE"));
    object->update(L"Job", std::wstring(L"CEO"));

    object = create<Core::Person>();
    object->update(L"name", std::wstring(L"Steve"));
    object->update(L"surname", std::wstring(L"Wosnyak"));
    object->update(L"sex", std::wstring(L"MALE"));
    object->update(L"Job", std::wstring(L"Enginear"));

    object = create<Core::Group>();
    object->update(L"name", std::wstring(L"Apple computers inc."));

    object = create<Core::Group>();
    object->update(L"name", std::wstring(L"Microsoft Corporation"));

    object = create<Core::Group>();
    object->update(L"name", std::wstring(L"XEROX PARC"));

    reset_cache();

    std::map<std::wstring, boost::any> args;

    if (search(args).size() != 7)
    {
        return -1;
    }

    args[L"name"] = std::wstring(L"Steve");

    if (search(args).size() != 2)
    {
        return -2;
    }

    args.clear();
    args[L"surname"] = std::wstring(L"Connor");
    args[L"Job"] = std::wstring(L"none");

    if (search(args).size() != 1)
    {
        return -3;
    }

    return 0;
}

