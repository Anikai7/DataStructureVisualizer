#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(const sf::Vector2f& size);
    void addOption(const std::string& imagePath);
    void render(sf::RenderWindow& window);
    bool handleClick(const sf::Vector2f& mousePos);

private:
    sf::RectangleShape background;
    std::vector<sf::Sprite> options;
    std::vector<sf::Texture> textures;
};

#endif // MENU_H
