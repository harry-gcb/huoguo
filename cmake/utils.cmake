aux_source_directory(${PROJECT_SOURCE_DIR}/utils/src UTILS_LIST)
add_library(utils STATIC ${UTILS_LIST})
add_library(huoguo::utils ALIAS utils)
target_include_directories(utils PUBLIC ${PROJECT_SOURCE_DIR}/utils/include)
