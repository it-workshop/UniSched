#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <event.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_CONNECT_EVENT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *event1 = create<Core::Event>();
    assert(event1);
    Core::Object *event2 = create<Core::Event>();
    assert(event2);
    Core::Object *group = create<Core::Group>();
    assert(group);
    bool cont = false;

    event1->connect(group);

    if (boost::any_cast<const std::vector<Core::Object *>&>(event1->read("children_groups")).size() != 1
        || boost::any_cast<const std::vector<Core::Object *>&>(group->read("parent_groups")).size() != 1)
    {
        return -1;
    }
    try
    {
        group->connect(event2);
    }
    catch(std::bad_cast& e)
    {
        std::cout << "Exception catched :) " << e.what() << std::endl;
        cont = true;
    }

    if (!cont)
    {
        return -1;
    }
    cont = false;

    try
    {
        event1->connect(event2);
    }
    catch(std::bad_cast& e)
    {
        std::cout << "Exception catched :) " << e.what() << std::endl;
        return 0;
    }

    return -2;
}

