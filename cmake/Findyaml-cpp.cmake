find_path(YAML_CPP_INCLUDE_DIR yaml-cpp/yaml.h)
find_library(YAML_CPP_LIBRARY NAMES yaml-cpp)

if (YAML_CPP_INCLUDE_DIR AND YAML_CPP_LIBRARY)
    set(YAML_CPP_FOUND TRUE)
endif (YAML_CPP_INCLUDE_DIR AND YAML_CPP_LIBRARY)

if (YAML_CPP_FOUND)
    if (NOT yaml-cpp_FIND_QUIETLY)
        message (STATUS "Found yaml-cpp: ${YAML_CPP_LIBRARY}")
    endif (NOT yaml-cpp_FIND_QUIETLY)
else (YAML_CPP_FOUND)
    if (yaml-cpp_FIND_REQUIRED)
        message (FATAL_ERROR "Could not find yaml-cpp")
    endif (yaml-cpp_FIND_REQUIRED)
endif (YAML_CPP_FOUND)

