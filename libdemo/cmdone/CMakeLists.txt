file(GLOB CMDONE_SOURCES "*.cpp")

add_executable(cmdone)

target_sources(
    cmdone
    PRIVATE ${CMDONE_SOURCES}
)

# 配置依赖
add_dependencies(
   cmdone
   dlibone
)

# target_link_libraries(
#     cmdone
#     libdlibone.so
# )