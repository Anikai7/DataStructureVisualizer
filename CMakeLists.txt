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

# Include directories for project headers
include_directories(
    ${CMAKE_SOURCE_DIR}/cpp/include
)

# Add nlohmann/json as a header-only library
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/cpp/src/*.cpp
    ${CMAKE_SOURCE_DIR}/cpp/src/main.cpp
)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable target
add_executable(DSV ${PROJECT_SOURCES})

# Link SFML libraries
if (SFML_FOUND)
    target_link_libraries(DSV sfml-graphics sfml-window sfml-system nlohmann_json)
else()
    message(FATAL_ERROR "SFML not found! Make sure SFML is installed.")
endif()

# Print project information
message(STATUS "Project binary directory: ${PROJECT_BINARY_DIR}")
message(STATUS "Project source directory: ${PROJECT_SOURCE_DIR}")
