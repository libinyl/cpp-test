cmake_minimum_required(VERSION 3.0)
project(cpp-test CXX)

set(CMAKE_CXX_STANDARD 20)
set(FINAL_TARGET cpp-test)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(pthread)
add_subdirectory(smartptr)

add_executable(${FINAL_TARGET} main.cpp)
target_link_libraries(${FINAL_TARGET} ${GTEST_BOTH_LIBRARIES} pthread smartptr)







