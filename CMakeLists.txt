cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debug/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debug/bin)

add_subdirectory(cmake)