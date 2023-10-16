cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/time_server TIME_SERVER)
add_executable(time_server ${TIME_SERVER})
target_link_libraries(time_server PRIVATE huoguo::net huoguo::utils)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/time_client TIME_CLIENT)
add_executable(time_client ${TIME_CLIENT})
target_link_libraries(time_client PRIVATE huoguo::net huoguo::utils)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/udp_echo UDP_ECHO)
add_executable(udp_echo ${UDP_ECHO})
target_link_libraries(udp_echo PRIVATE huoguo::net huoguo::utils)

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/rtsp_client RTSP_CLIENT)
# add_executable(rtsp_client ${RTSP_CLIENT})
# target_link_libraries(rtsp_client PRIVATE huoguo::rtsp huoguo::net huoguo::utils)