#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "guziksklep.h"
#include "guzik.h"
#include <vector>
#include "openall.h"
#include <sstream>
#include "gra.h"
#include <fstream>
#include "valuehandler.h"
#include "HoverDisplayss.h"
class Shop {

public:
    Shop(sf::RenderWindow& window); 
        std::ostringstream ss;
    void run();
~Shop();
private:
    static const size_t maxZbiornikSize = 100;
    Guziksklep buykernel1;
    Guziksklep buykernel2;
    Guziksklep buykernel3;
    Guziksklep buykernel4;
    Guziksklep buykernel5;
    Guziksklep buykernel6;
    Guziksklep buykernel7;
    Guziksklep buykernel8;
    Guziksklep buykernel9;
bool showLowMoneyMessage;
 sf::RenderWindow& window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
Openall* openall;
    bool isPszenicaPressed;
    bool openwerehouse = false;
    bool sorrywiondowisopen = true;
    char marchewkaznak = 'M';
    char pszenicaznak = 'P';
    char truskawkaznak = 'T';
    char jablkoznak = 'J';
    char gruszkaznak = 'G';
    char sliwkaznak = 'Z';
    char jajkoswinia = 'W';
    char jajkokrowa = 'K';
    char jajkokura = 'U';

    int licznik = 0;

    sf::Texture pricesset1;
    sf::Texture pricesset2;
    sf::Texture pricesset3;
    sf::Texture pricesset4;
    sf::Texture pricesset5;
    sf::Texture pricesset6;
    sf::Texture pricesset7;
    sf::Texture pricesset8;
    sf::Texture pricesset9;
    sf::Sprite price1;
    sf::Sprite price2;
    sf::Sprite price3;
    sf::Sprite price4;
    sf::Sprite price5;
    sf::Sprite price6;
    sf::Sprite price7;
    sf::Sprite price8;
    sf::Sprite price9;
    int liczba = 42;


    Guzik exit;
    sf::Texture exittextur;

    sf::Texture ziar1;
    sf::Texture ziar2;
    sf::Texture ziar3;
    sf::Texture ziar4;
    sf::Texture ziar5;
    sf::Texture ziar6;
    sf::Texture ziar7;
    sf::Texture ziar8;
    sf::Texture ziar9;

    sf::Texture pasek_zdj;
    sf::Sprite pasek;
    bool pomocotwarta = false;
    sf::Texture zapytaniezdj;
    sf::Sprite znakzapytania;
    sf::Texture tablicapomoczdj;
    sf::Sprite tablicapomoc;
    sf::Sprite wyjscietablica;
    std::vector<char> zbiornik;
    std::vector<char> wypisz;
    std::vector<int> letter;

    bool found;
    sf::Texture pointsphoto;
    sf::Sprite points;
sf::Font font;
sf::Text text;
int xPos;
    char Signs;
        int valuess;
    int zlotowki;
    sf::Text pieniadze;
HoverDisplays* hoverDisplay; 
HoverDisplays* hoverDisplay2; 
HoverDisplays* hoverDisplay3;
HoverDisplays* hoverDisplay4;
    sf::Texture obraz1;
    sf::Texture obraz2;
    sf::Texture obraz3;
    sf::Texture obraz4;
    sf::Texture obraz5;
    sf::Texture obraz6;
    sf::Texture obraz7;
    sf::Texture obraz8;
    sf::Texture obraz9;

    sf::Texture skrzynkazdj;
    sf::Sprite skrzynka;
 std::string zlotowkiStr;
 void addstorage();
    bool isRunning;
    void render();
    void handleEvents();
    void addprice();
    void addkernalforshelf();
    void tableforunder();
    void drawValuesAtBottom(); 
    void zlicz();
    void switchTofarm();
    void renderTopasek();
    void addhelp();
    void znakpomocy();
};