#ifndef DATA_RENDER_H
#define DATA_RENDER_H

#include<iostream>
#include"DataVisualizer.h"

void DrawCircle(sf::RenderWindow& window, int centerX, int centerY, int radius);
void renderVariables(sf::RenderWindow& window, const std::vector<Data*>& variables,sf::Vector2f cameraPos);

#endif