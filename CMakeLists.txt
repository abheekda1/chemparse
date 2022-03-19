cmake_minimum_required(VERSION 3.12)
project(chemical-formula-parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

set(SOURCE
    src/chemparse.cpp
    src/periodictable.cpp
    )

add_executable(chemparse
        ${SOURCE}
        src/main.cpp
        )
