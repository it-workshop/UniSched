cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "Building in sources not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

include (cmake/CMakeDependentOption.cmake)

option(CORE_ONLY "Собирать только ядро" OFF)
CMAKE_DEPENDENT_OPTION(WITH_SQLITE "Build with SQLite support." ON
        "NOT CORE_ONLY" OFF)
CMAKE_DEPENDENT_OPTION(WITH_DUMMYUI "Build with DummyUI support." ON
        "NOT CORE_ONLY" OFF)
CMAKE_DEPENDENT_OPTION(WITH_CLI "Build with CLI support." ON
        "NOT CORE_ONLY" OFF)
CMAKE_DEPENDENT_OPTION(WITH_YAML "Build with YAML support." ON
        "NOT CORE_ONLY" OFF)
CMAKE_DEPENDENT_OPTION(WITH_TESTS_CXX11 "Check if the compiler handles the C++11 stuff right." ON
        "NOT CORE_ONLY" OFF)
option(WITH_TESTS_CORE "Build with Core tests." OFF)
option(WITH_EXT_PYTHON_CLI "Экспериментальные питоновские биндинги к CLI. (лучше просто пройди мимо)" OFF)
CMAKE_DEPENDENT_OPTION(WITH_NCURSES "Build ncurses frontend." ON
        "NOT CORE_ONLY" OFF)

if (CORE_ONLY)
    message ("#################################")
    message ("Внимание, собирается только ядро.")
    message ("#################################")
endif (CORE_ONLY)


if (WITH_TESTS_CXX11)
    include (cmake/c++11/CheckCXX11Features.cmake)
endif (WITH_TESTS_CXX11)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

configure_file(src/modules/paths.hpp.in ${PROJECT_SOURCE_DIR}/src/include/paths.hpp)

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

if (WITH_SQLITE)
    find_package (sqlite REQUIRED)
endif (WITH_SQLITE)

if (WITH_NCURSES)
    find_package (ncurses REQUIRED)
endif (WITH_NCURSES)

include_directories ("${Boost_INCLUDE_DIRS}")
include_directories ("${PROJECT_SOURCE_DIR}/src/include")

enable_testing()

add_subdirectory (src)

