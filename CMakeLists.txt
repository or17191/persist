cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

option(test "Build all tests" ON)

set(PROJECT_NAME presist)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14") 

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
if(test)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/python_bind")
