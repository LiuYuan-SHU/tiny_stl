cmake_minimum_required(VERSION 3.17)

project("Tiny STL"
        VERSION 0.3.1
        DESCRIPTION "A subset of STL, implemented in C++17, CMake, XMake, GTest and Doxygen"
)

set(CMAKE_CXX_STANDARD 17)

# if is mode debug, export symbol
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/doc)
