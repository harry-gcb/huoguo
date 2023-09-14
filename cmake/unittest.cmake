enable_testing()
find_package(GTest REQUIRED)

if (NOT GTest_FOUND)
    message(FATAL_ERROR  "GTest Not Found")
else()
    message(STATUS "GTest Found done")
endif()

include(GoogleTest)
include(CTest)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils/test TEST_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/sdp/test TEST_LIST)
add_executable(unittest ${TEST_LIST})
target_link_libraries(unittest GTest::gtest GTest::gtest_main huoguo::sdp huoguo::utils)
gtest_discover_tests(unittest)

