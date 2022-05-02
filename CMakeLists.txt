cmake_minimum_required(VERSION 3.12)
project(chemparse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SOURCE
    src/chemparse/chemparse.cpp
    src/chemparse/Compound.cpp
    src/chemparse/Element.cpp
    src/chemparse/Equation.cpp
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

option(DOWNLOAD_CATCH2 "Download Catch2 framework if it won't be found locally" ON)

find_package(Catch2 3)

if(NOT Catch2_FOUND AND DOWNLOAD_CATCH2)
  include(FetchContent)

  FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v3.0.0-preview5
  )
  
  message("Catch2 v3 not found locally. Fetching it from the git repository...")
  FetchContent_MakeAvailable(catch2)
  set(FETCHCONTENT_UPDATES_DISCONNECTED_CATCH2 ON) # don't update

  set(Catch2_FOUND TRUE)
endif()

if(Catch2_FOUND)
  file(GLOB TEST_SRC "tests/*.cpp")
  add_executable(tests ${SOURCE} ${TEST_SRC})
  target_include_directories(tests PUBLIC include)
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
else()
  message("Catch2 v3 was not found and not dowloaded. Testing target won't be available.")
endif()
