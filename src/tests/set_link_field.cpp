#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME L"TESTINGUI_SET_LINK_FIELD"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *person = create<Core::Person>();
    assert(person);
    Core::Object *group = create<Core::Group>();
    assert(group);
    bool cont = false;

    try
    {
        person->update(L"groups", std::wstring(L"Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::wcout << "Exception is catched :) " << e.what() << std::endl;
        cont = true;
    }
    if (!cont)
    {
        return -1;
    }
    cont = false;
    try
    {
        group->update(L"people", std::wstring(L"Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::wcout << "Exception is catched :) " << e.what() << std::endl;
        cont = true;
    }
    if (!cont)
    {
        return -1;
    }

    try
    {
        group->update(L"parent_groups", std::wstring(L"Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::wcout << "Exception is catched :) " << e.what() << std::endl;
        return 0;
    }

    return -1;
}

