cmake_minimum_required(VERSION 3.20)
project(Sharingan_Example_SimpleUsage LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main project
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../" "${CMAKE_CURRENT_BINARY_DIR}/_deps/sharingan")

# Create executable
add_executable(${PROJECT_NAME})

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

# Link with Sharingan library
target_link_libraries(${PROJECT_NAME} PRIVATE Sharingan)
