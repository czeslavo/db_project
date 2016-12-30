file (GLOB COMMON_TESTS_SOURCE_FILES "common/*.cpp")
file (GLOB DB_TESTS_SOURCE_FILES "db/*.cpp")

add_executable (run_common_tests ${COMMON_TESTS_SOURCE_FILES})
target_link_libraries (run_common_tests gtest gtest_main common_lib)
add_test (common_tests run_common_tests)

add_executable (run_db_tests ${DB_TESTS_SOURCE_FILES})
target_link_libraries (run_db_tests gtest gtest_main common_lib db_lib models_lib)
add_test (db_tests run_db_tests)

