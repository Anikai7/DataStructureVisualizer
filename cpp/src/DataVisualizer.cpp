#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/DataVisualizer.h"
#include "../include/DataRender.h"
#include "imgui.h"
#include "../../imgui/backend/imgui_impl_sdl2.h"
#include "../../imgui/backend/imgui_impl_opengl3.h"

// For convenience
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

// Rendering function to display data
void DataVisualizer::render()
{
    if (variables.empty())
    {
        std::cerr << "Error: No data found in file.\n";
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

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, renderer);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Main loop
    bool running = true;
    SDL_Event event;

    // Camera/dragging logic
    int cameraX = 0, cameraY = 0;
    bool isDragging = false;
    int lastX, lastY;

    while (running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            // Handle mouse dragging for camera movement
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = true;
                lastX = event.button.x;
                lastY = event.button.y;
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = false;
            }
            if (event.type == SDL_MOUSEMOTION && isDragging)
            {
                int dx = event.motion.x - lastX;
                int dy = event.motion.y - lastY;
                cameraX += dx;
                cameraY += dy;
                lastX = event.motion.x;
                lastY = event.motion.y;
            }
        }

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create ImGui window
        ImGui::Begin("Controls");
        ImGui::Text("Data Structure Visualizer");
        ImGui::Text("Camera Position: (%d, %d)", cameraX, cameraY);

        // You can add more ImGui widgets here
        if (ImGui::Button("Reset Camera"))
        {
            cameraX = 0;
            cameraY = 0;
        }

        ImGui::End();

        // Clear the screen with a black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Call a rendering function to render variables
        renderVariables(renderer, variables, cameraX, cameraY);

        // Render ImGui UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Cleanup SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}