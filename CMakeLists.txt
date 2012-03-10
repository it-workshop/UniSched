cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

include (cmake/c++11/CheckCXX11Features.cmake)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

option(WITH_SQLITE "Build with SQLite support." N)
option(WITH_DUMMYUI "Build with DummyUI support." Y)
option(WITH_CLI "Build with CLI support." N)
option(WITH_YAML "Build with YAML support." Y)

find_package (Boost REQUIRED)

if (WITH_CLI)
    find_package (Readline REQUIRED)
endif (WITH_CLI)

if (WITH_YAML)
    add_definitions(-DWITH_YAML)
    find_package (yaml-cpp REQUIRED)
endif (WITH_YAML)

include_directories ("${Boost_INCLUDE_DIRS}")
include_directories ("${PROJECT_SOURCE_DIR}/src/include")


if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "Building in sources not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

enable_testing()

add_subdirectory (src)

