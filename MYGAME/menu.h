#pragma once
#include "guzik.h"
#include <SFML/Graphics.hpp>
#include "gra.h"

class Menu {

public:
    Menu();
    void run();

private:

    Guzik startgame;


    sf::RenderWindow window;
    bool isRunning;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture guzikTexture;





void switchToGame(); 
    void handleEvents();
    void render();
};
