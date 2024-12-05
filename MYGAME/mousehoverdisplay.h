
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

class MouseHoverDisplay
{
public:
    MouseHoverDisplay(sf::RenderWindow &window, const std::vector<char> &signs, bool limitedDisplay = true);
    void displayImageOnHover(const sf::Vector2i &mousePosition);

private:

    sf::RenderWindow &window;
    const std::vector<char> &signs;
    std::unordered_map<char, sf::Texture> images;
    sf::Sprite largeSprite;
    char currentHover;
    bool limitedDisplay;
    sf::Texture textureP;
    sf::Texture textureM;
    sf::Texture textureT;
    
    void loadImages();
    void displayLargeImage(const sf::Vector2f &position, const sf::Texture &texture);
    void createSprites();
    void hideLargeImage();
};
