cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_library(rtsp STATIC ${SRC_LIST})
add_library(huoguo::rtsp ALIAS rtsp)
target_include_directories(rtsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(rtsp PRIVATE huoguo::net)