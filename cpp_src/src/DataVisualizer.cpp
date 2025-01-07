#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "DataVisualizer.h"
#include "DataRender.h"

// For convenience
using json = nlohmann::json;

DataVisualizer::DataVisualizer(const std::string &filename)
{
    parseJSONFile(filename);
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

void DataVisualizer::render(){

    if (variables.empty())
    {
        std::cerr << "Error: No data found in file " << "\n";
        return;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error: SDL could not initialize. " << SDL_GetError() << "\n";
        return;
    }

    std::cout << "Window created\n";

    SDL_Window *window = SDL_CreateWindow("Data Structure Visualizer",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Error: Window could not be created. " << SDL_GetError() << "\n";
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        std::cerr << "Error: Renderer could not be created. " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Main loop
    bool running = true;
    SDL_Event event;

    cameraX = 0;
    cameraY = 0;
    bool isDragging = false;

    int lastX, lastY;

    while (running)
    {

        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            

        // Set the draw color to black (R, G, B, A)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        

        // Clear the entire screen with the current draw color
        SDL_RenderClear(renderer);
        renderVariables(renderer, variables);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}
