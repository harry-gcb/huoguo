enable_testing()
find_package(GTest REQUIRED)

if (NOT GTest_FOUND)
    message(FATAL_ERROR  "GTest Not Found")
else()
    message(STATUS "GTest Found done")
endif()

aux_source_directory(${CMAKE_SOURCE_DIR}/utils/test TEST_LIST)
add_executable(unittest ${TEST_LIST})
target_link_libraries(unittest GTest::gtest GTest::gtest_main huoguo::utils)

include(GoogleTest)
gtest_discover_tests(unittest)