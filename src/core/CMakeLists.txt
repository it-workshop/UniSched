cmake_minimum_required(VERSION 2.8)

if (USE_WINDOWS_SPIKE)
    set(WINDOWS_SPIKE_CPP windows-spike.cpp)
endif (USE_WINDOWS_SPIKE)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp
            object.cpp abstractui.cpp module.cpp ${WINDOWS_SPIKE_CPP}
            abstractstorage.cpp utils.cpp config.cpp)

if (NOT USE_WINDOWS_SPIKE)
    target_link_libraries (core dl)
endif (NOT USE_WINDOWS_SPIKE)

target_link_libraries (core ${Boost_LIBRARIES} ${LUA_LIBRARY})

