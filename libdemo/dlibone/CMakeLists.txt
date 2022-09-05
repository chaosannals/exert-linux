file(GLOB DLIBONE_SOURCES "*.cpp")

add_library(
    dlibone
    SHARED
    ${DLIBONE_SOURCES}
)