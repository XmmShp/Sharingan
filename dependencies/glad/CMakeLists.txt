cmake_minimum_required(VERSION 3.14)

set(GLAD_PATH ${CMAKE_CURRENT_LIST_DIR})
add_library(glad STATIC "${GLAD_PATH}/src/glad.c")
target_include_directories(glad PUBLIC "${GLAD_PATH}/include")
