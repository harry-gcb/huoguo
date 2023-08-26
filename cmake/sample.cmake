aux_source_directory(${PROJECT_SOURCE_DIR}/sample/time_server TIME_SERVER)
add_executable(time_server ${TIME_SERVER})
target_link_libraries(time_server PRIVATE huoguo::net huoguo::utils)

aux_source_directory(${PROJECT_SOURCE_DIR}/sample/time_client TIME_CLIENT)
add_executable(time_client ${TIME_CLIENT})
target_link_libraries(time_client PRIVATE huoguo::net huoguo::utils)

include_directories(${PROJECT_SOURCE_DIR}/rtsp/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/sample/rtsp_client RTSP_CLIENT)
add_executable(rtsp_client ${RTSP_CLIENT})
target_link_libraries(rtsp_client PRIVATE huoguo::rtsp huoguo::net huoguo::utils)


