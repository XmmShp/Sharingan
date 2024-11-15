cmake_minimum_required(VERSION 3.20)

project(Sharingan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(Sharingan INTERFACE)
target_include_directories(Sharingan INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

# ImGui dependencies

set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/dependencies/imgui")
add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE "${IMGUI_PATH}")

FILE(GLOB IMGUI_SOURCES "${IMGUI_PATH}/*.cpp")

target_sources(imgui INTERFACE ${IMGUI_SOURCES})
target_sources(imgui INTERFACE "${IMGUI_PATH}/backends/imgui_impl_glfw.cpp")
target_sources(imgui INTERFACE "${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp")

target_link_libraries(Sharingan INTERFACE imgui)


