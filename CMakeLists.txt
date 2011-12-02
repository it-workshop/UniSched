cmake_minimum_required (VERSION 2.8)
project (UniSched)

add_definitions (-std=c++0x)
include_directories ("${PROJECT_SOURCE_DIR}/src/include")

add_subdirectory (src)

