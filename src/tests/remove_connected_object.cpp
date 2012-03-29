#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME L"TESTINGUI_REMOVE_CONNECTED_OBJECT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *John = create<Core::Person>();
    assert(John);
    Core::Object *James = create<Core::Person>();
    assert(James);
    Core::Object *group1 = create<Core::Group>();
    assert(group1);
    Core::Object *group2 = create<Core::Group>();
    assert(group2);

    John->connect(group1);
    John->connect(group2);
    group1->connect(James);
    group2->connect(James);
    group2->connect(group1);

    remove(group1);
    remove(James);

    if (boost::any_cast<std::vector<Core::Object *>>(John->read(L"groups")).size() != 1)
    {
        return -1;
    }
    if (boost::any_cast<std::vector<Core::Object *>>(group2->read(L"people")).size() != 1)
    {
        return -2;
    }
    if (boost::any_cast<std::vector<Core::Object *>>(group2->read(L"children_groups")).size())
    {
        return -3;
    }

    return 0;
}

