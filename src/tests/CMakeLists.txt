cmake_minimum_required (VERSION 2.8)

add_executable (model_classes_are_real model_classes_are_real.cpp)
target_link_libraries (model_classes_are_real backend core storage ui)
add_test (test_model_classes_are_real model_classes_are_real)

add_executable (architecture_with_backends architecture_with_backends.cpp)
target_link_libraries (architecture_with_backends backend core storage ui)
if (HAVE_SQLITE)
    target_link_libraries (architecture_with_backends sqlitestorage)
endif (HAVE_SQLITE)
add_test (test_arcitecture_with_backends architecture_with_backends)

