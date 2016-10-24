cmake_minimum_required(VERSION 3.5)
include(ExternalProject)

option(test "Build all tests" ON)

set(PROJECT_NAME presist)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14") 

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories("${CMAKE_SOURCE_DIR}/include")
if(test)
	add_subdirectory("/usr/src/gtest" "${CMAKE_BINARY_DIR}/gtest")
	enable_testing()
	
	include_directories("${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}")
	add_executable(unittest test_list.cpp)
	target_link_libraries(unittest gtest gtest_main)
	add_test(NAME cpp COMMAND unittest)

	add_test(NAME python COMMAND python3 -m pytest "${CMAKE_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()

execute_process(COMMAND python-config --cflags OUTPUT_VARIABLE PYBIND_CF_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REPLACE "2.7" "3.5" PYBIND_CF_FLAGS ${PYBIND_CF_FLAGS})
separate_arguments(PYBIND_CF_FLAGS)
execute_process(COMMAND python-config --ldflags OUTPUT_VARIABLE PYBIND_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REPLACE "2.7" "3.5" PYBIND_LD_FLAGS ${PYBIND_LD_FLAGS})
separate_arguments(PYBIND_LD_FLAGS)
add_library(pyrsist SHARED python_bind/module.cpp)
target_compile_options(pyrsist PRIVATE ${PYBIND_CF_FLAGS})
target_compile_options(pyrsist PRIVATE ${PYBIND_LD_FLAGS})
set_target_properties(pyrsist PROPERTIES PREFIX "")
