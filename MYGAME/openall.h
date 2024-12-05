#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
//#include "mousehoverdisplay.h"

class Openall {
public:
    Openall(sf::RenderWindow& window, std::vector<char>& charvalues,std::vector<int>& intvalues);
    void drawtank();
    void addsToPasek();
    void handleMouseEvent(const sf::Event& event);
        std::vector<char> getCharValues() const;
    std::vector<int> getIntValues() const;
private:
//MouseHoverDisplay hoverDisplay;
    sf::RenderWindow& window;
    sf::Texture werehousephoto;
    sf::Sprite werehouse;
    std::vector<char>& charvalues;
    std::vector<int>& intvalues;
    sf::Texture carrottolinephoto;
sf::Texture strawberrytolinephoto;
sf::Sprite carrottoline;
sf::Sprite strawberrytoline;
sf::Font font;



  bool firstItemSelected;
    char firstItem, secondItem;
    sf::Vector2f firstItemPosition, secondItemPosition;



    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;
    sf::Sprite sprite6;
    sf::Sprite sprite7;
    sf::Sprite sprite8;
    sf::Sprite sprite9;
    sf::Sprite sprite10;
    sf::Sprite sprite11;
    sf::Sprite sprite12;
    sf::Sprite sprite13;
    sf::Sprite sprite14;
    sf::Sprite sprite15;
    sf::Sprite sprite16;
    sf::Texture obraz1;
    sf::Texture obraz2;
    sf::Texture obraz3;
    sf::Texture obraz4;
    sf::Texture obraz5;
    sf::Texture obraz6;
    sf::Texture obraz7;
    sf::Texture obraz8;
    sf::Texture obraz9;
    sf::Texture obraz10;
    sf::Texture obraz11;
    sf::Texture obraz12;
    sf::Texture obraz13;
    sf::Texture obraz14;
    sf::Texture obraz15;
    sf::Texture obraz16;
        int xPos;
        int position;
        sf::Text text;
    void checkForItemSelection(const sf::Vector2f& mousePos);
    void swapItems();
    sf::Vector2f getItemPosition(char item);
    void setPosition(char item, const sf::Vector2f& pos);
    sf::Vector2f getItemSize(char item);
    void enlargeItem(char item, bool enlarge = true);
    void swapCharValues(char first, char second);

};