#include "HoverDisplayss.h"

HoverDisplays::HoverDisplays(sf::RenderWindow& window, char& sign, float left, float right, float top, float bottom)
: window(window), sign(sign), left(left), right(right), top(top), bottom(bottom) {
    loadTextures();
    sprite.setPosition(right, top - 90); 
    sprite.setScale(0.2f, 0.2f);
}

void HoverDisplays::update() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

    if (worldPos.x >= left && worldPos.x <= right && worldPos.y >= top && worldPos.y <= bottom) {
        sprite.setTexture(textures[sign]);
        window.draw(sprite);
    }
}

void HoverDisplays::loadTextures() {
    sf::Texture texture;
    texture.loadFromFile("tablicazdj/przenicatablica.png");
    textures['P'] = texture;

    texture.loadFromFile("tablicazdj/marchewkanasionotablica.png");
    textures['M'] = texture;

    texture.loadFromFile("tablicazdj/truskawkanasiono_tablica.png");
    textures['T'] = texture;

        texture.loadFromFile("tablicazdj/marchewka_tablica.png");
    textures['C'] = texture;

        texture.loadFromFile("tablicazdj/truskawka_tablica.png");
    textures['S'] = texture;

        texture.loadFromFile("tablicazdj/jablkonasiono_tablica.png");
    textures['J'] = texture;

        texture.loadFromFile("tablicazdj/gruszkanasiono_tablica.png");
    textures['G'] = texture;

        texture.loadFromFile("tablicazdj/sliwkanasiono_tablica.png");
    textures['Z'] = texture;

        texture.loadFromFile("tablicazdj/jablko_tablica.png");
    textures['A'] = texture;

        texture.loadFromFile("tablicazdj/gruszka_tablica.png");
    textures['E'] = texture;

        texture.loadFromFile("tablicazdj/sliwka_tablica.png");
    textures['F'] = texture;

        texture.loadFromFile("tablicazdj/sztabka_miedzi_tablica.png");
    textures['I'] = texture;

        texture.loadFromFile("tablicazdj/sztabka_srebra_tablica.png");
    textures['R'] = texture;

        texture.loadFromFile("tablicazdj/sztabka_zlota_tablica.png");
    textures['L'] = texture;

        texture.loadFromFile("tablicazdj/diament_tablica.png");
    textures['D'] = texture;

    texture.loadFromFile("tablicazdj/jajko_swini_tablica.png");
    textures['W'] = texture;

        texture.loadFromFile("tablicazdj/jajko_krowy_tablica.png");
    textures['K'] = texture;

        texture.loadFromFile("tablicazdj/jajko_kury_tablica.png");
    textures['U'] = texture;

    // Dodaj więcej tekstur dla innych znaków tutaj
}
