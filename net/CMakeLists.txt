cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_library(net STATIC ${SRC_LIST})
add_library(huoguo::net ALIAS net)
target_link_libraries(net PUBLIC huoguo::utils)
target_include_directories(net PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_definitions(net PRIVATE NET_LINUX)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows") 
    target_compile_definitions(net PRIVATE NET_WIN32)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin") 
    target_compile_definitions(net PRIVATE NET_MACOS)
ELSE () 
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}") 
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sample/time_server TIME_SERVER)
add_executable(time_server ${TIME_SERVER})
target_link_libraries(time_server PRIVATE huoguo::net huoguo::utils)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sample/time_client TIME_CLIENT)
add_executable(time_client ${TIME_CLIENT})
target_link_libraries(time_client PRIVATE huoguo::net huoguo::utils)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtsp/include)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sample/rtsp_client RTSP_CLIENT)
# add_executable(rtsp_client ${RTSP_CLIENT})
# target_link_libraries(rtsp_client PRIVATE huoguo::rtsp huoguo::net huoguo::utils)