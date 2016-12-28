file (GLOB COMMON_TESTS_SOURCE_FILES "common/*.cpp")

add_executable (run_common_tests ${COMMON_TESTS_SOURCE_FILES})
target_link_libraries (run_common_tests gtest gtest_main common_lib)
add_test (common_tests run_common_tests)

