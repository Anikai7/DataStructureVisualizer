#include "menu.h"

Menu::Menu(const sf::Vector2f& size) {
    background.setSize(size);
    background.setFillColor(sf::Color(50, 50, 50));
}

void Menu::addOption(const std::string& imagePath) {
    sf::Texture texture;
    if (texture.loadFromFile(imagePath)) {
        textures.push_back(texture);
        sf::Sprite sprite(textures.back());
        sprite.setPosition(20, 80 + options.size() * 100); // Adjust position
        options.push_back(sprite);
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(background);
    for (auto& option : options) {
        window.draw(option);
    }
}

bool Menu::handleClick(const sf::Vector2f& mousePos) {
    for (auto& option : options) {
        if (option.getGlobalBounds().contains(mousePos)) {
            // Handle the click
            return true;
        }
    }
    return false;
}
