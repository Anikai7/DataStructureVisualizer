#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include "../include/DataVisualizer.h"

void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    const int segmentCount = 360;  // Increased number of segments for a smoother circle

    // Iterate over the angle from 0 to 360 degrees, calculating the circle's points
    for (int i = 0; i < segmentCount; ++i) {
        float angle = i * (2 * M_PI / segmentCount);  // Calculate the angle
        int x = centerX + static_cast<int>(radius * cos(angle));  // X position of the point
        int y = centerY + static_cast<int>(radius * sin(angle));  // Y position of the point

        // Draw the point at the calculated position
        SDL_RenderDrawPoint(renderer, x, y);
    }
}


void renderVariables(SDL_Renderer* renderer, const std::vector<Data*>& variables,int cameraX,int cameraY) {
    int x = 0, y = 0;

    for (const auto& var : variables) {
        // Draw a circle for each variables
        DrawCircle(renderer,x,y,30);
        var->objPos.first = x;
        var->objPos.second = y;
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        y += 120; // Move down for the next variable
    }
}
