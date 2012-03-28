cmake_minimum_required(VERSION 2.6)

add_library(ncursesui SHARED main.cpp)
target_link_libraries(ncursesui ncurses)

