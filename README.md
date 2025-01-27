# Data Structure Visualizer

Data Structure Visualizer is a C++ project designed to provide an intuitive graphical interface for visualizing and analyzing data structures. The application allows users to input C++ source files and dynamically explore the relationships between data structures, their structure, and runtime details, including variable values and memory addresses.

## Planned Features

- **Graphical Visualization**: Utilizes Vulkan for high-performance, cross-platform rendering.
- **Dynamic Analysis**: Leverages libclang to parse and extract information from C++ source files.
- **Runtime Details**: Displays values and memory addresses of variables within the data structures.
- **C++ Exclusive**: Focused solely on parsing and visualizing C++ codebases.

## Prerequisites

### Tools and Libraries
- **Graphics Libraries**: 
  - [Vulkan SDK](https://vulkan.lunarg.com/) (for graphics rendering)
- **Parsing Library**: 
  - [libclang](https://clang.llvm.org/docs/Tooling.html) (for source file analysis)
- **Build System**: CMake

## Installation

### Clone the Repository
```bash
git clone https://github.com/yourusername/dataStructureVisualizer.git
cd dataStructureVisualizer
```

### Build the Project
1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
2. Run CMake:
   ```bash
   cmake ..
   ```
3. Build the project:
   ```bash
   cmake --build .
   ```

## Usage

1. Launch the application after building:
   ```bash
   ./dataStructureVisualizer
   ```
2. Load a C++ source file via the application interface.
3. Explore data structures and their properties through the interactive visualization.