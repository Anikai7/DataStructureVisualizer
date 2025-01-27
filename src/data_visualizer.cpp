#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <data_visualizer.h>
#include <decl_parsing.hpp>

// Rendering function to display data
void DataVisualizer::render(std::vector<ClassStructInfo> classesAndStructs)
{
    if (classesAndStructs.empty())
    {
        std::cerr << "Error: No data found in file.\n";
        return;
    }
    
    for (auto i : classesAndStructs) {
        std::cout << i.name << " " << std::endl;
        for (auto j : i.fields) {
            std::cout << j.type << " " << j.name << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }

    return;
}