cmake_minimum_required(VERSION 2.6)

if (WITH_NCURSES)
    add_library(ncursesui SHARED main.cpp)
    target_link_libraries(ncursesui ncurses)
endif (WITH_NCURSES)

