cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DataStructureVisualizer VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type (default to Debug)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define directories
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/ImGui)
set(NLOHMANN_DIR ${CMAKE_SOURCE_DIR}/external)

# Collect project sources
file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/paeser/*.cpp
)

# ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

# Find and link Vulkan
find_package(Vulkan REQUIRED)

# GLFW setup
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Don't build GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Don't build GLFW tests")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Don't build GLFW docs")
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "Enable Vulkan support in GLFW")
add_subdirectory(external/glfw)

# Add executable target
add_executable(DSV ${PROJECT_SOURCES} ${IMGUI_SOURCES})

# Include directories for the executable
target_include_directories(DSV PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${IMGUI_DIR}/include
    ${IMGUI_DIR}/backends
    ${NLOHMANN_DIR}
    "E:/coding/clang+llvm-19.1.7-x86_64-pc-windows-msvc/include"
)

# Link libraries
target_link_libraries(DSV PRIVATE
    Vulkan::Vulkan
    glfw
    "E:/coding/clang+llvm-19.1.7-x86_64-pc-windows-msvc/lib/libclang.lib"
)
