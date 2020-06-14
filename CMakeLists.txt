cmake_minimum_required(VERSION 3.0)
project(stl-test CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB SOURCEFILE *.cpp)

add_executable(stl-test ${SOURCEFILE})
target_link_libraries(stl-test ${GTEST_BOTH_LIBRARIES})









