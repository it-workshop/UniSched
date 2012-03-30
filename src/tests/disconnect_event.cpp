#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <event.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_DISCONNECT_EVENT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *event1 = create<Core::Event>();
    assert(event1);
    Core::Object *group = create<Core::Group>();
    assert(group);

    event1->connect(group);
    event1->disconnect(group);

    if (boost::any_cast<const std::vector<Core::Object *>&>(event1->read("children_groups")).size()
        || boost::any_cast<const std::vector<Core::Object *>&>(group->read("parent_groups")).size())
    {
        return -1;
    }

    return 0;
}

