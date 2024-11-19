#include <iostream>
#include "DataVisualizer.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp> // JSON library

DataVisualizer::DataVisualizer(const std::string& filename) {
    loadFromFile(filename);
}

void DataVisualizer::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    nlohmann::json j;
    try {
        infile >> j;
        if (j.empty()) {
            std::cerr << "JSON file is empty." << std::endl;
            return;
        }

        for (const auto& item : j["data_structures"]) {
            DataStructure ds;
            ds.name = item["name"];
            ds.data = item["data"].get<std::vector<std::string>>();
            data_structures.push_back(ds);
        }

        std::cout << "Loaded data structures from JSON: " << data_structures.size() << " items" << std::endl;
    } catch (nlohmann::json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }
}

void DataVisualizer::render() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Data Structure Visualizer");
    window.setVerticalSyncEnabled(false);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Could not load font." << std::endl;
        return;
    }

    std::cout << "Starting render loop" << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);  // Clear window with a white background
        std::cout << "Window cleared" << std::endl;

        for (size_t i = 0; i < data_structures.size(); ++i) {
            sf::CircleShape shape(50);
            shape.setFillColor(sf::Color::Blue);
            shape.setPosition(100, 100 + 120 * i);
            window.draw(shape);
            std::cout << "Drawing shape" << std::endl;

            sf::Text text;
            text.setFont(font);
            text.setString(data_structures[i].name);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Black);
            text.setPosition(160, 100 + 120 * i);
            window.draw(text);
            std::cout << "Drawing text: " << data_structures[i].name << std::endl;
        }

        window.display();
        std::cout << "Window displayed" << std::endl;
    }
}
