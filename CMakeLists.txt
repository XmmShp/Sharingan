cmake_minimum_required(VERSION 3.20)

project(Sharingan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(Sharingan INTERFACE)
target_include_directories(Sharingan INTERFACE "./include")

# glad dependencies

add_library(glad STATIC "./dependencies/glad/src/glad.c")
target_include_directories(glad PUBLIC "./dependencies/glad/include")
target_link_libraries(Sharingan INTERFACE glad)

# glfw dependencies

add_subdirectory("./dependencies/glfw")

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

target_link_libraries(Sharingan INTERFACE glfw)

# ImGui dependencies

add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE "./dependencies/imgui" "./dependencies/imgui/backends")

FILE(GLOB IMGUI_SOURCES "./dependencies/imgui/*.cpp")
target_sources(imgui INTERFACE ${IMGUI_SOURCES}
        "./dependencies/imgui/backends/imgui_impl_glfw.cpp"
        "./dependencies/imgui/backends/imgui_impl_opengl3.cpp"
)

target_link_libraries(Sharingan INTERFACE imgui)


