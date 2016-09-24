cmake_minimum_required(VERSION 3.5)

option(test "Build all tests" ON)

set(PROJECT_NAME presist)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wpedantic")

if(test)
	enable_testing()
	include_directories(${gtest_SOURCE_DIR}/indclude ${gtest_SOURCE_DIR})
	add_executable(unittest unittest.cpp)
	add_test(NAME unittests COMMAND unittests)
endif()

