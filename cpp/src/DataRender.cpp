#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "DataVisualizer.h" // Adjust the path based on your directory structure

// Function to draw a circle
void drawCircle(sf::RenderWindow& window, int centerX, int centerY, int radius) {
    sf::CircleShape circle(radius);  // Create a circle with the given radius
    circle.setPosition(centerX - radius, centerY - radius);  // Adjust position for circle origin
    circle.setFillColor(sf::Color::Transparent);  // Make the circle hollow
    circle.setOutlineThickness(2);  // Set the outline thickness
    circle.setOutlineColor(sf::Color::White);  // Set the outline color
    window.draw(circle);  // Draw the circle on the window
}

// Function to render variables
void renderVariables(sf::RenderWindow& window, const std::vector<Data*>& variables, sf::Vector2f cameraPos) {
    int x = 100 + static_cast<int>(cameraPos.x);  // Initial x position, offset by the camera
    int y = 100 + static_cast<int>(cameraPos.y);  // Initial y position, offset by the camera

    for (const auto& var : variables) {
        // Draw a circle for each variable
        drawCircle(window, x, y, 30);

        // Update the object's position
        var->objPos.first = x;
        var->objPos.second = y;

        // Move down for the next variable
        y += 120;
    }
}