cmake_minimum_required(VERSION 3.12)
project(chemical-formula-parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src/include)

add_executable(chemparse
        src/chemparse.cpp
        src/main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/periodic-table.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)