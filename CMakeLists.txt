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

# Include directories for SDL2 and other libraries
include_directories(
    ${CMAKE_SOURCE_DIR}/cpp_src/include
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/include
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${CMAKE_SOURCE_DIR}/external/SDL2/include  # Add SDL2 headers
)

# Add SDL2 source files
file(GLOB SDL2_SOURCES
    ${CMAKE_SOURCE_DIR}/external/SDL2/src/*.c
    ${CMAKE_SOURCE_DIR}/external/SDL2/src/main/*.c
)

# Add nlohmann/json as a header-only library
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/cpp/src/*.cpp
    ${CMAKE_SOURCE_DIR}/cpp/src/main.cpp
)

# Add ImGui source files
file(GLOB IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add executable target
add_executable(DSV ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${SDL2_SOURCES})

# Link libraries
if (OpenGL_FOUND)
    target_link_libraries(DSV OpenGL::GL nlohmann_json)
else()
    message(FATAL_ERROR "OpenGL not found! Make sure OpenGL is installed.")
endif()

# Print project information
message(STATUS "Project binary directory: ${PROJECT_BINARY_DIR}")
message(STATUS "Project source directory: ${PROJECT_SOURCE_DIR}")
