cmake_minimum_required(VERSION 3.20)

project(Sharingan LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(Sharingan INTERFACE)
target_include_directories(Sharingan INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

# ImGui dependencies

set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/dependencies/imgui")
add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE "${IMGUI_PATH}")

FILE(GLOB_RECURSE IMGUI_SOURCES "${IMGUI_PATH}/*.cpp")

if (NOT ANDROID)
    list(REMOVE_ITEM IMGUI_SOURCES "${IMGUI_PATH}/backends/imgui_impl_android.cpp")
endif ()

target_sources(imgui INTERFACE ${IMGUI_SOURCES})

target_link_libraries(Sharingan INTERFACE imgui)


