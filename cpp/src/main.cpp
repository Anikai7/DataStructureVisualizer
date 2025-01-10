#include <DataVisualizer.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Constructor to initialize DataVisualizer with a filename
DataVisualizer::DataVisualizer(const std::string &filename)
{
    parseJSONFile(filename); // Parse the JSON data
}

// Function to parse JSON file
void DataVisualizer::parseJSONFile(const std::string &filename)
{
    // Read JSON file
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename;
        return;
    }

    json data;
    try
    {
        file >> data;
        if (data.empty())
        {
            std::cerr << "JSON file is empty." << std::endl;
            return;
        }

        if (data.contains("variables") && data["variables"].is_array())
        {
            // Loop through the "variables" key in the JSON data and store them
            for (const auto &item : data["variables"])
            {
                Data *tem = new Data;
                tem->name = item["name"];
                tem->type = item["type"];
                variables.push_back(tem); // Store variable
            }
        }
        else
        {
            std::cerr << "Error: Missing or invalid 'variables' key in the JSON file." << std::endl;
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }
    return;
}

int main() {
    DataVisualizer visualizer("/home/ani/Coding/projects/DataStructureVisualizer/variables.json");
    visualizer.render();
    return 0;
}