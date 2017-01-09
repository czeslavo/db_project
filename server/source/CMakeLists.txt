file (GLOB COMMON_SOURCE_FILES "common/*.cpp"
                               "common/http_headers/*.cpp")
file (GLOB API_SOURCE_FILES "api/*.cpp"
                            "api/handlers/*.cpp")
file (GLOB DB_SOURCE_FILES "db/*.cpp")
file (GLOB MODELS_SOURCE_FILES "models/*.cpp")
file (GLOB MAIN_SOURCE_FILES "*.cpp")
file (GLOB INITIALIZER_MAIN_SOURCE_FILES "db/initializer/*.cpp")


SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS
    log log_setup system filesystem date_time thread)
include_directories(${Boost_INCLUDE_DIRS})

add_library(common_lib ${COMMON_SOURCE_FILES})
target_link_libraries(common_lib ${Boost_LIBRARIES})

add_library(models_lib ${MODELS_SOURCE_FILES})

add_library(api_lib ${API_SOURCE_FILES})
target_link_libraries(api_lib net_static pthread common_lib db_lib)

add_library(db_lib ${DB_SOURCE_FILES})
target_link_libraries(db_lib pqxx pthread)

add_executable(run_server ${MAIN_SOURCE_FILES})
target_link_libraries(run_server common_lib api_lib models_lib)

add_executable(run_initializer ${INITIALIZER_MAIN_SOURCE_FILES})
target_link_libraries(run_initializer db_lib common_lib)

install(TARGETS run_server run_initializer DESTINATION ${flat_mate_server_SOURCE_DIR}/artifacts)
