cmake_minimum_required(VERSION 3.21)
project(chem_molar_mass)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(src/include)

add_executable(chem_molar_mass
        src/chemparse.cpp
        src/main.cpp)
