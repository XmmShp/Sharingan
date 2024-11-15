cmake_minimum_required(VERSION 3.20)

project(Sharingan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(Sharingan SHARED)
target_include_directories(Sharingan PUBLIC "./include")

# ImGui dependencies

add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE "./dependencies/imgui" "./dependencies/imgui/backends")

FILE(GLOB IMGUI_SOURCES "./dependencies/imgui/*.cpp")
target_sources(imgui INTERFACE ${IMGUI_SOURCES}
        "./dependencies/imgui/backends/imgui_impl_glfw.cpp"
        "./dependencies/imgui/backends/imgui_impl_opengl3.cpp"
)

target_link_libraries(Sharingan INTERFACE imgui)


