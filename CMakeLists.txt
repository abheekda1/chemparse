cmake_minimum_required(VERSION 3.21)
project(chemical-formula-parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/include)

add_executable(chemparse
        src/chemparse.cpp
        src/main.cpp)
