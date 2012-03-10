cmake_minimum_required(VERSION 2.8)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp object.cpp abstractui.cpp module.cpp)

if (YAML_CPP STREQUAL YAML_CPP-NOTFOUND)
    message (FATAL_ERROR "Could not find yaml-cpp. Minimun version reqiured: 0.5.0")
else (YAML_CPP STREQUAL YAML_CPP-NOTFOUND)
    message (STATUS "Found Yaml-cpp: " ${YAML_CPP})
    target_link_libraries (core yaml-cpp ${Boost_LIBRARIES})
endif (YAML_CPP STREQUAL YAML_CPP-NOTFOUND)
