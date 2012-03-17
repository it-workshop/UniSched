cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "Building in sources not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

option(WITH_SQLITE "Build with SQLite support." N)
option(WITH_DUMMYUI "Build with DummyUI support." Y)
option(WITH_CLI "Build with CLI support." Y)
option(WITH_YAML "Build with YAML support." Y)
option(WITH_TESTS_CXX11 "Check if the compiler handles the C++11 stuff right." Y)
option(WITH_TESTS_CORE "Build with Core tests." N)
option(WITH_EXT_PYTHON_CLI "Экспериментальные питоновские биндинги к CLI. (лучше просто пройди мимо)" N)

if (WITH_TESTS_CXX11)
    include (cmake/c++11/CheckCXX11Features.cmake)
endif (WITH_TESTS_CXX11)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

configure_file(src/modules/paths.hpp.in ${PROJECT_SOURCE_DIR}/src/modules/paths.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

find_package (Boost REQUIRED)

if (WITH_YAML)
    add_definitions(-DWITH_YAML)
    find_package (yaml-cpp REQUIRED)
endif (WITH_YAML)

if (WITH_TESTS_CORE)
   add_definitions(-DWITH_TESTS_CORE)
endif (WITH_TESTS_CORE)

if (WITH_EXT_PYTHON_CLI)
    add_definitions(-DWITH_EXT_PYTHON_CLI)
endif(WITH_EXT_PYTHON_CLI)

include_directories ("${Boost_INCLUDE_DIRS}")
include_directories ("${PROJECT_SOURCE_DIR}/src/include")

enable_testing()

add_subdirectory (src)

