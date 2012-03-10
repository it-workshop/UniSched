cmake_minimum_required (VERSION 2.8)

add_executable (tester tester.cpp)
target_link_libraries (tester core)

add_library (create_person SHARED create_person.cpp)
add_test (create_person_test tester --iface TESTINGUI_CREATE_PERSON)

add_library (create_group SHARED create_group.cpp)
add_test (create_group_test tester --iface TESTINGUI_CREATE_GROUP)
