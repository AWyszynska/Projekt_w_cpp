#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class HoverDisplays {
public:
    HoverDisplays(sf::RenderWindow& window, char& sign, float left, float right, float top, float bottom);

    void update();

private:
    void loadTextures();

    sf::RenderWindow& window;
    char sign;
    float left, right, top, bottom;
    sf::Sprite sprite;
    std::unordered_map<char, sf::Texture> textures;
};


