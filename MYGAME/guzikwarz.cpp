#include "guzikwarz.h"
#include <SFML/Graphics.hpp>


GuzikWarzywa::GuzikWarzywa(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
    : window(window), position(position), size(size) {
    guzikShape.setPosition(position);
    guzikShape.setSize(size);

    targetSize = size;
}

void GuzikWarzywa::setTexture(const sf::Texture& texture) {
    guzikTexture = texture;
    guzikShape.setTexture(&guzikTexture);
}

void GuzikWarzywa::draw() {
    window.draw(guzikShape);
}

bool GuzikWarzywa::isClicked(const sf::Vector2i& mousePosition) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
    return guzikShape.getGlobalBounds().contains(mousePos);
}

bool GuzikWarzywa::isHoveredButton() const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
    return guzikShape.getGlobalBounds().contains(mousePos);
}

void GuzikWarzywa::handleMouseInteraction() {
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