cmake_minimum_required(VERSION 3.20)
project(dut_program_design)

set(CMAKE_CXX_STANDARD 14)

add_executable(dut_program_design src/data.cpp src/data.h src/file.cpp src/file.h src/io.cpp src/io.h src/util.cpp src/util.h src/main.cpp)
