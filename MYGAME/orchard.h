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
#include "HoverDisplayss.h"

class Orchard
{

public:
    Orchard(sf::RenderWindow &window);

    std::vector<char> ReadSigns;
    std::vector<int> Readvalues;
    void handleSadzonkaInteraction();
    void changeImage();
    void run();
    ~Orchard();

private:
    struct DisplayedImage
    {
        sf::Sprite sprite;
        sf::Time timer;
        bool isThirdImageDisplayed = false;
        float positionX = 0.0f;
    };
    std::vector<sf::Clock> clocksadzonki;
    sf::Clock newClock;
    Openall *openall;
    float differenceInSeconds;
    std::chrono::duration<double> difference = std::chrono::duration<double>::zero();
    std::vector<DisplayedImage> displayedImages;
    bool clicked = false;
    sf::RenderWindow &window;
    std::vector<float> timess;
    sf::Time addedtime;
    bool isSadzonkaPressed;
    bool isRunning;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    int currentImage;
HoverDisplays* hoverDisplay; 
HoverDisplays* hoverDisplay2; 
HoverDisplays* hoverDisplay3;
HoverDisplays* hoverDisplay4;
    std::vector<float> positions;
    sf::Clock clock;

    sf::Texture ziarno1;
    float currentX = 200;
    float imageSpacing = 280.0f;

    std::vector<sf::Clock> timeElapsed;
    float maxDisplayTime = 4.0f;

    std::vector<int> positionss;

    bool testy = false;

    Guzik exit;
    sf::Texture exittextur;
    sf::Texture pasek;
    sf::Texture kopiec;
    sf::Texture pszenica;
    int zlotowkiValue = 0;
    sf::Font font;
    sf::Text zlotowkiText;
    std::ifstream zlotowkiFile;
    int added = 0;
    sf::Time initialTime;
    sf::Text text;

    char Signs;

    int valuess;
    int xPos;
    sf::Clock myClock;

    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;
    sf::Sprite sprite6;
    sf::Sprite sprite7;
    sf::Sprite sprite8;
    sf::Sprite sprite9;

    bool zasadzonepszenica = true;
    bool zasadzonemarchew = true;
    bool zasadzonetruskawka = true;

    sf::Texture carrottolinephoto;
    sf::Texture strawberrytolinephoto;
    sf::Sprite carrottoline;
    sf::Sprite strawberrytoline;
    sf::Texture psze1;
    sf::Texture psze2;
    sf::Texture psze3;

    sf::Texture mar1;
    sf::Texture mar2;
    sf::Texture mar3;

    sf::Texture tru1;
    sf::Texture tru2;
    sf::Texture tru3;

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
    sf::Sprite pszenica2;
    sf::Sprite pasek2;
    sf::Sprite dokopiec;
    sf::Sprite dokopiec2;
    sf::Sprite dokopiec3;

    sf::Texture marchewzdj;
    sf::Sprite marchew;
    sf::Texture truskawkazdj;
    sf::Sprite truskawka;
    sf::Vector2f originalScale;
    std::vector<char> planting;
    int position;
    sf::Texture tankphoto;
    sf::Texture pointsphoto;
    sf::Sprite points;

    char plantt;
    bool openwerehouse = false;
    bool sorrywiondowisopen = true;

    time_t czas;
    tm *czas_info;
    bool pomocotwarta = false;
    sf::Texture zapytaniezdj;
    sf::Sprite znakzapytania;
    sf::Texture tablicapomoczdj;
    sf::Sprite tablicapomoc;
    sf::Sprite wyjscietablica;
    std::vector<sf::Sprite> pszenicaSprites;

    void handleEvents();
    void render();
    void kopcephoto();
    void switchTofarm();
    void renderTopasek();
    void addToPasek();
    void savePositions();
    void saveTimes();
    void savePlantingInfo();
    void savetimeall();
    void loadPlantingInfo();
    void loadPositions();
    void loadTimes();
    void savepositionAdditional();
    void addstorage();
    void bleeaddtoline();
    void switchplace();
    bool addedblee = false;
    void addhelp();
    void znakpomocy();
};