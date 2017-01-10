file (GLOB COMMON_TESTS_SOURCE_FILES "common/*.cpp")
file (GLOB DB_TESTS_SOURCE_FILES "db/*.cpp")
file (GLOB API_TESTS_SOURCE_FILES "api/*.cpp")

add_executable (run_common_tests ${COMMON_TESTS_SOURCE_FILES})
target_link_libraries (run_common_tests gtest gtest_main common_lib net_static)
add_test (common_tests run_common_tests)

add_executable (run_db_tests ${DB_TESTS_SOURCE_FILES})
target_link_libraries (run_db_tests gtest gtest_main common_lib db_lib models_lib)
add_test (db_tests run_db_tests)

add_executable (run_api_tests ${API_TESTS_SOURCE_FILES})
target_link_libraries (run_api_tests gmock gtest gtest_main models_lib api_lib)
add_test (api_tests run_api_tests)
