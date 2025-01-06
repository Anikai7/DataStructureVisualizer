# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DataStructureVisualizer VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable debugging information
set(CMAKE_BUILD_TYPE Debug)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/cpp_src/include)
include_directories(/usr/local/include)

# Find SDL2
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    message(STATUS "SDL2 found: ${SDL2_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "SDL2 not found! Please install SDL2 development libraries.")
endif ()

# Include nlohmann/json as a header-only library
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Add Python interpreter (optional for Clang workflow)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
if (Python3_FOUND)
    message(STATUS "Python3 found: ${Python3_EXECUTABLE}")
else ()
    message(FATAL_ERROR "Python3 not found! Make sure Python3 is installed.")
endif ()

# Add source files
add_executable(DSV
    cpp_src/src/main.cpp
    cpp_src/src/DataVisualizer.cpp
    cpp_src/src/DataRender.cpp
)

# Link SDL2 and JSON libraries
target_link_libraries(DSV ${SDL2_LIBRARIES} nlohmann_json)

# Print project information
message(STATUS "Project binary directory: ${PROJECT_BINARY_DIR}")
message(STATUS "Project source directory: ${PROJECT_SOURCE_DIR}")
