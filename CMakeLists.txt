cmake_minimum_required(VERSION 3.17)

project("FractalEngine")

set( CMAKE_CXX_FLAGS  "-fPIC" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set (CMAKE_CXX_STANDARD 17)

add_subdirectory("ftul")
add_subdirectory("modules")
add_subdirectory("loader")
