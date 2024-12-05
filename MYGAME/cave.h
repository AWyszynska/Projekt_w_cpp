#pragma once
#include "guzikwarz.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "gra.h"
#include "guzik.h"
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include "openall.h"
#include <random>
//#include "mousehoverdisplay.h"
class Cave
{

public:
    Cave(sf::RenderWindow &window);

    void run();
    ~Cave();

private:
    Guzik exit;
    sf::Texture exittextur;
    sf::RenderWindow &window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    Openall *openall;
    sf::Texture pasek_zdj;
    sf::Sprite pasek;
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
    sf::Texture skrzynkazdj;
    sf::Sprite skrzynka;
    sf::Texture carrottolinephoto;
    sf::Texture strawberrytolinephoto;
    sf::Sprite carrottoline;
    sf::Sprite strawberrytoline;
    std::vector<char> ReadSigns;
    int xPos;
    char Signs;

    bool genereTopasek = false;

    sf::Text text;
    std::vector<int> Readvalues;
    int valuess;
    bool openwerehouse = false;
    sf::Texture pointsphoto;
    sf::Sprite points;
    int zlotowkiValue = 0;
    sf::Font font;
    sf::Text zlotowkiText;
    std::ifstream zlotowkiFile;
    float randomScale;
    float scaleFactorX;
    int scaleSteps;
    bool pomocotwarta = false;
    sf::Texture zapytaniezdj;
    sf::Sprite znakzapytania;
    sf::Texture tablicapomoczdj;
    sf::Sprite tablicapomoc;
    sf::Sprite wyjscietablica;
    float randomPercent;
    int licznik = 0;
    std::vector<std::string> imagePaths;
    std::vector<sf::Texture> texturespath;
    std::random_device rd;
    bool isShowing = false;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    bool isGrowing = false;
    bool isRightMouseDown = false;
    sf::Clock rightClickTimer;
    sf::Texture skala1zdj;
    sf::Sprite skala1;
    sf::Clock clockskala;
    sf::Time elapsedskala;
    sf::Clock timer; // Declare a timer
    bool isHoldingSkala = false;
    bool stop = true;
    bool test = false;
    float scale = 1.0f;
    void switchTofarm();
    void handleEvents();
    void render();
    void switchplace();
    void addToPasek();
    void renderTopasek();
    void addstorage();
    void renderskala();
    void losowacskala();
    void genere_to_pasek();
    void addhelp();
    void znakpomocy();
};
