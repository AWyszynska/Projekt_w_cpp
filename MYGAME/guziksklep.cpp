#include "guziksklep.h"
#include <SFML/Graphics.hpp>
Guziksklep::Guziksklep(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
    : window(window), position(position), size(size) {
    guzikShape.setPosition(position);
    guzikShape.setSize(size);

    targetSize = size;
}

void Guziksklep::setTexture(const sf::Texture& texture) {
    guzikTexture = texture;
    guzikShape.setTexture(&guzikTexture);
}

void Guziksklep::draw() {
    window.draw(guzikShape);
}

bool Guziksklep::isClicked(const sf::Vector2i& mousePosition) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
    return guzikShape.getGlobalBounds().contains(mousePos);
}

bool Guziksklep::isHoveredButton() const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
    return guzikShape.getGlobalBounds().contains(mousePos);
}

void Guziksklep::handleMouseInteraction() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);

    if (guzikShape.getGlobalBounds().contains(mousePos)) {
        targetSize = size * 1.2f;
    }
    else {
        targetSize = size;
    }

    sf::Vector2f currentSize = guzikShape.getSize();
    sf::Vector2f newSize = currentSize + (targetSize - currentSize) * 0.1f;
    guzikShape.setSize(newSize);
}
