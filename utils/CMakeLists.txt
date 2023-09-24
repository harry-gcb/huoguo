cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_library(utils STATIC ${SRC_LIST})
add_library(huoguo::utils ALIAS utils)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_LIST)
add_executable(utils_unittest ${TEST_LIST})
target_link_libraries(utils_unittest GTest::gtest GTest::gtest_main huoguo::utils)
gtest_discover_tests(utils_unittest)
