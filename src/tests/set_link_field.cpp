#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_SET_LINK_FIELD"
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
        person->update("groups", std::string("Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        cont = true;
    }
    if (!cont)
    {
        return -1;
    }
    cont = false;
    try
    {
        group->update("people", std::string("Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        cont = true;
    }
    if (!cont)
    {
        return -1;
    }

    try
    {
        group->update("parent_groups", std::string("Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        return 0;
    }

    return -1;
}

