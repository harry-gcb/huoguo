include_directories(${PROJECT_SOURCE_DIR}/app/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/app/src SRC_LIST)
add_executable(huoguo ${SRC_LIST})
target_link_libraries(huoguo PRIVATE huoguo::rtsp huoguo::net huoguo::utils crypto ssl)
