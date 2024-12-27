cmake_minimum_required(VERSION 3.10)
project(DataStructureVisualizer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include the nlohmann/json header-only library
find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp)
include_directories(${NLOHMANN_JSON_INCLUDE_DIR})

# Add the executable
add_executable(DSV src/main.cpp src/DataVisualizer.cpp)

# Link libraries
target_link_libraries(DSV ${SDL2_LIBRARIES})


