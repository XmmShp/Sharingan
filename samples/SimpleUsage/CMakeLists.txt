cmake_minimum_required(VERSION 3.20)

project(Sharingan_Example_SimpleUsage LANGUAGES C CXX)

add_subdirectory("../../" "./_external/Sharingan")

set(CMAKE_CXX_STANDARD 11)

add_executable(Sharingan_Example_SimpleUsage)
FILE(GLOB_RECURSE Sharingan_Example_SimpleUsage_SOURCES "./src/*.cpp")

target_sources(Sharingan_Example_SimpleUsage PUBLIC ${Sharingan_Example_SimpleUsage_SOURCES})
target_link_libraries(Sharingan_Example_SimpleUsage Sharingan)

add_subdirectory("../dependencies/glfw" "./_external/glfw")
target_link_libraries(Sharingan_Example_SimpleUsage glfw)

add_subdirectory("../dependencies/glad" "./_external/glad")
target_link_libraries(Sharingan_Example_SimpleUsage glad)
