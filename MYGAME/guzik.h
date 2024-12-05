// guzik.h
#ifndef GUZIK_H
#define GUZIK_H

#include <SFML/Graphics.hpp>

class Guzik
{
public:
    Guzik(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size);
    void draw();
    void handleMouseInteraction();
    bool isHoveredButton() const;
    void setTexture(const sf::Texture &texture);
    bool isClicked(const sf::Vector2i &mousePosition) const;

private:
    sf::RenderWindow &window;
    sf::RectangleShape guzikShape;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f targetSize;
    sf::Texture guzikTexture;
};

#endif
