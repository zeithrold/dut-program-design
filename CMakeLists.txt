cmake_minimum_required(VERSION 3.20)
project(dut_program_design)


add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 14)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_example/health_info.csv  ${CMAKE_CURRENT_BINARY_DIR}/health_info.csv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_example/pcr_test_result_info.csv  ${CMAKE_CURRENT_BINARY_DIR}/pcr_test_result_info.csv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_example/people.csv  ${CMAKE_CURRENT_BINARY_DIR}/people.csv COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data_example/vaccine_info.csv  ${CMAKE_CURRENT_BINARY_DIR}/vaccine_info.csv COPYONLY)

add_executable(dut_program_design src/data.cpp src/data.h src/file.cpp src/file.h src/io.cpp src/io.h src/util.cpp src/util.h src/main.cpp)
