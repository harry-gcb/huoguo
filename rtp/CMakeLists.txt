cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src RTP_LIST)
add_library(rtp STATIC ${RTP_LIST})
add_library(huoguo::rtp ALIAS rtp)
target_include_directories(rtp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(rtp PUBLIC huoguo::net)

if (${BUILD_SAMPLE})
    message(STATUS "build rtp with sample")
    add_subdirectory(sample)
endif()