#include "mousehoverdisplay.h"
#include <iostream>

MouseHoverDisplay::MouseHoverDisplay(sf::RenderWindow &window, const std::vector<char> &signs, bool limitedDisplay)
    : window(window), signs(signs), limitedDisplay(limitedDisplay)
{
    loadImages();
}

void MouseHoverDisplay::loadImages()
{
    std::unordered_map<char, std::string> imagePaths = {
        {'P', "tablicazdj/przenicatablica.png"},
        {'M', "tablicazdj/marchewkanasionotablica.png"},
        {'T', "tablicazdj/truskawkanasiono_tablica.png"},
        {'C', "tablicazdj/marchewka_tablica.png"},
        {'S', "tablicazdj/truskawka_tablica.png"},
        {'J', "tablicazdj/jablkonasiono_tablica.png"},
        {'G', "tablicazdj/gruszkanasiono_tablica.png"},
        {'Z', "tablicazdj/sliwkanasiono_tablica.png"},
        {'A', "tablicazdj/jablko_tablica.png"},
        {'E',"tablicazdj/gruszka_tablica.png"},
        {'F', "tablicazdj/sliwka_tablica.png"},
        {'I', "tablicazdj/sztabka_miedzi_tablica.png"},
        {'R', "tablicazdj/sztabka_srebra_tablica.png"},
        {'L', "tablicazdj/sztabka_zlota_tablica.png"},
        {'D', "tablicazdj/diament_tablica.png"},
        {'W', "tablicazdj/jajko_swini_tablica.png"},
        {'K', "tablicazdj/jajko_krowy_tablica.png"},
        {'U', "tablicazdj/jajko_kury_tablica.png"},
    };

    for (const auto &pair : imagePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(pair.second)) {
            std::cerr << "Błąd ładowania obrazu: " << pair.second << std::endl;
        } else {
            images[pair.first] = texture;
        }
    }
}

void MouseHoverDisplay::displayImageOnHover(const sf::Vector2i &mousePosition)
{
    bool spriteHovered = false;
    int positionX = 280; 
    const int positionY = 700; 
    const int spriteWidth = 100; 

    for (const auto &sign : signs)
    {
        if (images.find(sign) != images.end())
        {
            sf::Sprite sprite(images.at(sign));
            sprite.setPosition(positionX, positionY); 
            sprite.setScale(0.5f, 0.5f);
            sf::FloatRect spriteBounds(positionX, positionY, spriteWidth, sprite.getGlobalBounds().height);
            if (spriteBounds.contains(static_cast<sf::Vector2f>(mousePosition)))
            {
                displayLargeImage(sprite.getPosition(), images.at(sign));
                spriteHovered = true;
                break;

            }

            positionX += spriteWidth + 50;
        }
            
    }

    if (!spriteHovered)
    {
        hideLargeImage(); 
    }

}



void MouseHoverDisplay::displayLargeImage(const sf::Vector2f &position, const sf::Texture &texture)
{
    largeSprite.setTexture(texture);
    largeSprite.setPosition(position.x + 90, position.y - 90);
    largeSprite.setScale(0.2f, 0.2f);
    window.draw(largeSprite);
    
}
void MouseHoverDisplay::hideLargeImage()
{

    largeSprite.setTexture(sf::Texture());
}