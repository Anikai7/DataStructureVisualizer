#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <DataVisualizer.h>
#include <DataRender.h>

// Rendering function to display data
void DataVisualizer::render()
{
    if (variables.empty())
    {
        std::cerr << "Error: No data found in file.\n";
        return;
    }

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Data Structure Visualizer");
    window.setFramerateLimit(60);

    // Camera position for panning
    sf::Vector2f cameraOffset(0.f, 0.f);
    bool isDragging = false;
    sf::Vector2i lastMousePos;

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle mouse dragging for camera movement
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = true;
                lastMousePos = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = false;
            }
            if (event.type == sf::Event::MouseMoved && isDragging)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f delta = static_cast<sf::Vector2f>(mousePos - lastMousePos);
                cameraOffset += delta;
                lastMousePos = mousePos;
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw variables
        renderVariables(window, variables, cameraOffset);

        // Display the rendered frame
        window.display();
    }
}