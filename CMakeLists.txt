cmake_minimum_required(VERSION 3.12)
project(chemparse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE
    src/chemparse/chemparse.cpp
    src/chemparse/util/periodictable.cpp
    )

add_executable(chemparse-bin ${SOURCE} src/main.cpp)
add_library(chemparse-lib ${SOURCE})

target_include_directories(chemparse-bin PUBLIC include)
target_include_directories(chemparse-lib PUBLIC include)

set_target_properties(chemparse-bin PROPERTIES OUTPUT_NAME chemparse)
set_target_properties(chemparse-lib PROPERTIES OUTPUT_NAME chemparse)
