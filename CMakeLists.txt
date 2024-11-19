cmake_minimum_required(VERSION 3.10)
project(DataStructureVisualizer)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find necessary packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add executable
add_executable(DataStructureVisualizer src/main.cpp src/DataVisualizer.cpp)

# Link libraries
target_link_libraries(DataStructureVisualizer
  sfml-graphics sfml-window sfml-system
  nlohmann_json::nlohmann_json
)

