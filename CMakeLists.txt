cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message(FATAL_ERROR  "GTest Not Found")
else()
    message(STATUS "GTest Found done")
endif()
include(GoogleTest)
include(CTest)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)

add_subdirectory(utils)
add_subdirectory(sdp)
add_subdirectory(net)
add_subdirectory(rtp)
add_subdirectory(rtsp)
add_subdirectory(app)
