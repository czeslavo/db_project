cmake_minimum_required (VERSION 3.0.0)
project (flat_mate_server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB HEADER_FILES "include/*.h")

add_subdirectory (source)
include_directories (source)

find_package(GTest)
if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    ADD_SUBDIRECTORY (externals/googletest-release-1.8.0)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

enable_testing()
add_subdirectory(tests)
