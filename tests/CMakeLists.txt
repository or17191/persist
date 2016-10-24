cmake_minimum_required(VERSION 3.5)

add_subdirectory("/usr/src/gtest" "${CMAKE_BINARY_DIR}/gtest")
enable_testing()

include_directories("${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}")
add_executable(unittest test_list.cpp)
target_link_libraries(unittest gtest gtest_main)
add_test(NAME cpp COMMAND unittest)

add_test(NAME python COMMAND python3 -m pytest "${CMAKE_CURRENT_SOURCE_DIR}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../python_bind")
