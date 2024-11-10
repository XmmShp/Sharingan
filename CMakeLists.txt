cmake_minimum_required(VERSION 3.20)

project(Sharingan_BasicUsage LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sharingan_BasicUsage "./src/main.cpp")

add_subdirectory("./Sharingan")
target_link_libraries(Sharingan_BasicUsage Sharingan)