file (GLOB COMMON_SOURCE_FILES "common/*.cpp")

set(SOURCE_FILES
    ${COMMON_SOURCE_FILES}
)

add_library(common_lib ${COMMON_SOURCE_FILES})

