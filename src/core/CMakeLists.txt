cmake_minimum_required(VERSION 2.8)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp object.cpp abstractui.cpp module.cpp)

target_link_libraries (core dl ${Boost_LIBRARIES})

if (WITH_YAML)
    target_link_libraries (core yaml-cpp)
endif (WITH_YAML)

