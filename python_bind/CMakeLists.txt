cmake_minimum_required(VERSION 3.5)

set(pyconfig "python3.5-config")

execute_process(COMMAND ${pyconfig} --cflags OUTPUT_VARIABLE PYBIND_CF_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(PYBIND_CF_FLAGS)
execute_process(COMMAND ${pyconfig} --ldflags OUTPUT_VARIABLE PYBIND_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(PYBIND_LD_FLAGS)
add_library(pyrsist SHARED module.cpp list.cpp)
target_compile_options(pyrsist PRIVATE ${PYBIND_CF_FLAGS})
target_compile_options(pyrsist PRIVATE ${PYBIND_LD_FLAGS})
set_target_properties(pyrsist PROPERTIES PREFIX "")
