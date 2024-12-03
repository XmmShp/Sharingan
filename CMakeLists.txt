cmake_minimum_required(VERSION 3.20)
project(Sharingan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find required packages
find_package(OpenGL REQUIRED)

# Setup GLAD
add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/src/glad.c"
)
target_include_directories(glad PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include"
)
target_link_libraries(glad PUBLIC OpenGL::GL)

# Setup GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw")

# Setup ImGui
set(IMGUI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui")
add_library(imgui STATIC)

file(GLOB IMGUI_SOURCES 
    "${IMGUI_PATH}/*.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp"
)

target_sources(imgui PRIVATE ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
    "${IMGUI_PATH}"
    "${IMGUI_PATH}/backends"
)

# Link ImGui dependencies
target_link_libraries(imgui PUBLIC 
    glad
    glfw
)

# Setup main library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(${PROJECT_NAME} INTERFACE 
    glad
    glfw
    imgui
)

# Create cmake config files for find_package support
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)
