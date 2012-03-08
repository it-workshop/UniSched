cmake_minimum_required(VERSION 2.8)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp object.cpp
                abstractui.cpp module.cpp)

target_link_libraries (core yaml-cpp ${Boost_LIBRARIES})

