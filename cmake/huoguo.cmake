aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable(huoguo ${SRC_LIST})
target_link_libraries(huoguo PRIVATE huoguo::utils)
