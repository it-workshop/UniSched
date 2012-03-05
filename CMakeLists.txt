cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

include_directories ("${PROJECT_SOURCE_DIR}/src/include")

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "In source build not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

enable_testing()

option(WITH_SQLITE "Build with SQLite support." N)
option(WITH_DUMMYUI "Build with DummyUI support." N)

add_subdirectory (src)

