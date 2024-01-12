cmake_minimum_required(VERSION 3.17)

project("FractalEngine")

add_subdirectory("ftul")
add_subdirectory("modules")
add_subdirectory("loader")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")