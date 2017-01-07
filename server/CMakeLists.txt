cmake_minimum_required (VERSION 3.0.0)
project (flat_mate_server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-std=c++1z")

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
                     ${CMAKE_CURRENT_SOURCE_DIR}/externals/json)
file(GLOB HEADER_FILES "include/*.h")

file(COPY ../scripts/init_db.sql DESTINATION /tmp/)
file(COPY ../scripts/fill_db.sql DESTINATION /tmp/)

add_subdirectory (source)
include_directories (source)

find_package(GTest)
if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    ADD_SUBDIRECTORY (externals/googletest-release-1.8.0)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include)
endif()

enable_testing()
add_subdirectory(tests)

