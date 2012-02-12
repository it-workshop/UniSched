cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

include_directories ("${PROJECT_SOURCE_DIR}/src/include")

set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/bin)

enable_testing()

option(WITH_SQLITE "Build with SQLite support." N)

add_subdirectory (src)

