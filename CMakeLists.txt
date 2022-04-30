cmake_minimum_required(VERSION 3.12)
project(chemparse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SOURCE
    src/chemparse/chemparse.cpp
    src/chemparse/util/periodictable.cpp
    )

add_executable(chemparse-bin ${SOURCE} src/main.cpp)
add_library(chemparse-dynamic-lib SHARED ${SOURCE})
add_library(chemparse-static-lib STATIC ${SOURCE})

target_include_directories(chemparse-bin PUBLIC include)
target_include_directories(chemparse-dynamic-lib PUBLIC include)
target_include_directories(chemparse-static-lib PUBLIC include)

set_target_properties(chemparse-bin PROPERTIES OUTPUT_NAME chemparse)
set_target_properties(chemparse-dynamic-lib PROPERTIES OUTPUT_NAME chemparse)
set_target_properties(chemparse-static-lib PROPERTIES OUTPUT_NAME chemparse)
