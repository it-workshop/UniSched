#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_CONNECT_PERSON"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *John = create<Core::Person>();
    assert(John);
    Core::Object *James = create<Core::Person>();
    assert(James);
    Core::Object *group = create<Core::Group>();
    assert(group);

    John->connect(group);
    group->connect(James);

    if (boost::any_cast<const std::vector<Core::Object *>&>(group->read("people")).size() != 2
        || boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size() != 1
        || boost::any_cast<const std::vector<Core::Object *>&>(James->read("groups")).size() != 1)
    {
        std::cout << boost::any_cast<const std::vector<Core::Object *>&>(group->read("people")).size() << " "
            << boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size() << " "
            << boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size()
            << std::endl;
        return -1;
    }

    try
    {
        John->connect(James);
    }
    catch (std::bad_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        return 0;
    }

    return -2;
}

