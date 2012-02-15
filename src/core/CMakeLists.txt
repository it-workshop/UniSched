cmake_minimum_required(VERSION 2.8)

add_library (core person.cpp abstractgroup.cpp group.cpp event.cpp manager.cpp
             manageableobject.cpp field.cpp)

target_link_libraries (core yaml-cpp)

