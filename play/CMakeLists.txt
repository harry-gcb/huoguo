cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PLAYER_LIST)
add_library(play STATIC ${PLAYER_LIST})
add_library(huoguo::play ALIAS play)
target_include_directories(play PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(FFMPEG REQUIRED)
if (FFMPEG_FOUND)
    target_include_directories(play PRIVATE ${FFMPEG_INCLUDE_DIRS})
    target_link_directories(play PRIVATE ${FFMPEG_LIBRARY_DIRS})
    target_link_libraries(play PRIVATE ${FFMPEG_LIBRARIES})
endif()
