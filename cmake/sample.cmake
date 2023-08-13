aux_source_directory(${PROJECT_SOURCE_DIR}/sample/time_server TIME_SERVER)
add_executable(time_server ${TIME_SERVER})
target_link_libraries(time_server PRIVATE huoguo::net huoguo::utils)
