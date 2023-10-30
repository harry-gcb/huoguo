cmake_minimum_required(VERSION 3.12.0)

project(huoguo)

find_package(OpenSSL REQUIRED)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_library(utils STATIC ${SRC_LIST})
add_library(huoguo::utils ALIAS utils)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(utils PRIVATE OpenSSL::Crypto)
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin") 
ELSE () 
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}") 
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

if (${BUILD_TEST})
# enable_testing()

# target_link_libraries(unittest PRIVATE GTest::gtest GTest::gtest_main huoguo::utils)

enable_testing()

find_package(GTest CONFIG REQUIRED)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_LIST)
add_executable(utils_unittest ${TEST_LIST})
target_link_libraries(utils_unittest PRIVATE huoguo::utils GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain main)
#gtest_discover_tests(unittest)
endif()


