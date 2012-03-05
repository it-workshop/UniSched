cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

include_directories ("${PROJECT_SOURCE_DIR}/src/include")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package (Readline REQUIRED)

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "In source build not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")


enable_testing()

option(WITH_SQLITE "Build with SQLite support." N)
option(WITH_DUMMYUI "Build with DummyUI support." N)
option(WITH_CLI "Build with CLI support." Y)

add_subdirectory (src)

