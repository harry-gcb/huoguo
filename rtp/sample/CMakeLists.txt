cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/debug TIME_SERVER)
add_executable(debug ${TIME_SERVER})
target_link_libraries(debug PRIVATE huoguo::rtp huoguo::net huoguo::utils)
