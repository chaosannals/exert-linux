cmake_minimum_required (VERSION 3.14)

project(libdemo)

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out/build")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out/build")

add_subdirectory(dlibone)
add_subdirectory(cmdone)
