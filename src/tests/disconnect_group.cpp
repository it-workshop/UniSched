#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME L"TESTINGUI_DISCONNECT_GROUP"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *group1 = create<Core::Group>();
    assert(group1);
    Core::Object *group2 = create<Core::Group>();
    assert(group2);

    group1->connect(group2);
    group1->disconnect(group2);

    if (boost::any_cast<const std::vector<Core::Object *>&>(group1->read(L"children_groups")).size()
        || boost::any_cast<const std::vector<Core::Object *>&>(group2->read(L"parent_groups")).size())
    {
        return -1;
    }

    return 0;
}

