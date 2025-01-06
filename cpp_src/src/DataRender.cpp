#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include"DataVisualizer.h"


void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    const int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y) {
        // Draw 8 points (octants) of the circle
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void renderVariables(SDL_Renderer* renderer, const std::vector<Data*>& variables) {
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
