#include<SDL2/SDL.h>
#include"DataVisualizer.h"

SDL_Event event;

bool isDragging = false;

int lastX, lastY;

void cameraPos(){
    if (event.type == SDL_MOUSEMOTION){
        if (isDragging){
            int x, y;
            SDL_GetMouseState(&x, &y);
            // Calculate how much the mouse moved
            int dx = x - lastX;
            int dy = y - lastY;
            // Update the camera position or orientation based on dx and dy
            // For example, cameraX and cameraY represent the camera's position
            cameraX += dx;
            cameraY += dy;
            // Update the last mouse position
            lastX = x;
            lastY = y;

            printf("CameraX: %d, CameraY: %d\n", cameraX, cameraY);
            }
            }   
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    isDragging = true;
                    SDL_GetMouseState(&lastX, &lastY);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    isDragging = false;
                }
            }
}
