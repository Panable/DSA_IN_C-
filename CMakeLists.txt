cmake_minimum_required(VERSION 3.26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(
Chelton #Name of Project
VERSION 1.0.0 #Current Version
LANGUAGES C CXX #Languages used
)

set(CMAKE_CXX_STANDARD 17) #C++ Version Being Compiled

add_subdirectory(src)
