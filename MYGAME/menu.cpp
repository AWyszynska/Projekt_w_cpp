#include "menu.h"
#include "guzik.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "gra.h"
Menu::Menu() : window(sf::VideoMode(1200, 800), "handlarz"), isRunning(true),
               startgame(window, sf::Vector2f(440, 240), sf::Vector2f(320, 320)) {
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("tlomenu.jpg")) {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    background.setTexture(backgroundTexture);

    if (!guzikTexture.loadFromFile("aazdj/guzikmenu.png")) {
        std::cout << "blad\n";
    }
    startgame.setTexture(guzikTexture);
}

void Menu::run() {
    while (window.isOpen()) {
        handleEvents();
        render();


    }
}

void Menu::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
            
            if (startgame.isHoveredButton()) {
                switchToGame();
            }
        }
    }
}

void Menu::render() {
    window.clear();
    window.draw(background);
    startgame.handleMouseInteraction();
    startgame.draw();
    window.display();
}

void Menu::switchToGame() {

    Game game(window);
    game.run();
}









