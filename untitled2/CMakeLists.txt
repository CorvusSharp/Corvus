cmake_minimum_required(VERSION 3.25)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp matrix_utils.h matrix_utils_impl.h processes.cpp threads.cpp parallel.cpp)
