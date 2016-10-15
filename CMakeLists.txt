cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

option(test "Build all tests" ON)

set(PROJECT_NAME presist)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14") 

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if(test)
	add_subdirectory("/usr/src/gtest" "${CMAKE_BINARY_DIR}/gtest")
	enable_testing()
	
	include_directories("${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}")
	add_executable(unittest unittest.cpp)
	target_link_libraries(unittest gtest gtest_main)
	add_test(NAME unittest COMMAND unittest)
endif()

