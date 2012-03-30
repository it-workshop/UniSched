cmake_minimum_required(VERSION 2.8)

add_library (repeat SHARED repeat.cpp)
target_link_libraries (repeat core)

