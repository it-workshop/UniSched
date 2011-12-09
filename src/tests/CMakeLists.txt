cmake_minimum_required (VERSION 2.8)

add_executable (model_classes_are_real model_classes_are_real.cpp)
target_link_libraries (model_classes_are_real core storage ui)

add_test (test_model_classes_are_real model_classes_are_real)

