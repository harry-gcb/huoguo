cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/app/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_executable(huoguo ${SRC_LIST})
target_include_directories(huoguo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(huoguo PRIVATE huoguo::rtsp huoguo::net huoguo::sdp huoguo::utils crypto ssl)