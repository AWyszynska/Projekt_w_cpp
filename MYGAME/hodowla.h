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
#include "timerbar.h"
#include "HoverDisplayss.h"
class Hodowla
{

public:
    Hodowla(sf::RenderWindow &window);

    void run();
    ~Hodowla();

private:
    float czasswinia;
    float czaskrowa;
    float czaskura;
    TimerBar *timerBar;
    TimerBar *timerBarkrowa;
    TimerBar *timerBarkura;
    Guzik exit;
    sf::Texture exittextur;
    sf::RenderWindow &window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    HoverDisplays* hoverDisplay; 
    HoverDisplays* hoverDisplay2; 
    HoverDisplays* hoverDisplay3;
    HoverDisplays* hoverDisplay4;
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
    sf::Texture plotzdj;
    sf::Sprite plot;
    bool pomocotwarta = false;
    sf::Texture zapytaniezdj;
    sf::Sprite znakzapytania;
    sf::Texture tablicapomoczdj;
    sf::Sprite tablicapomoc;
    sf::Sprite wyjscietablica;

    sf::Texture krowazdj;
    sf::Sprite krowa;
    sf::Texture kurazdj;
    sf::Sprite kura;
    sf::Vector2f size;
    sf::Vector2f targetSize;
    sf::Texture swiniazdj;
    sf::Sprite swinia;
    sf::Sprite ziarenko;
    sf::Texture carrottolinephoto;
    sf::Texture strawberrytolinephoto;
    sf::Sprite carrottoline;
    sf::Sprite strawberrytoline;
    std::vector<char> ReadSigns;
    int xPos;
    char Signs;
    sf::Text text;
    bool isKrowaAlive = true;
    bool isSwiniaAlive = true;
    bool isKuraAlive = true;
    std::vector<int> Readvalues;
    int valuess;
    bool openwerehouse = false;
    sf::Texture pointsphoto;
    sf::Sprite points;
    int zlotowkiValue = 0;
    sf::Font font;
    sf::Text zlotowkiText;
    std::ifstream zlotowkiFile;
    float speedMultiplier;
    bool ziarenkoClicked = false;

    void loadAnimalPositions();
    void saveAnimalPositions();

    float differenceInSeconds;
    std::chrono::duration<double> difference = std::chrono::duration<double>::zero();
    bool initializeds = false;

    bool shouldStops = false;
    sf::Clock stopClocks;
    // const float stopTimes = 5.f;
    time_t czas;
    tm *czas_info;
    sf::Texture swiniaEndTexture;
    sf::Texture krowaEndTexture;
    sf::Texture kuraEndTexture;
    float remainingTimeSwinia;
    float remainingTimeKrowa;
    float remainingTimeKura;
    sf::Texture zdjklodka;
    sf::Sprite klodkaswinia;
    sf::Sprite klodkakrowa;
    sf::Sprite klodkakura;

    bool swinkazyje;
    bool krowkazyje;
    bool kurkazyje;

    sf::Vector2f initialPositionKrowa;
    sf::Vector2f initialPositionSwinia;
    sf::Vector2f initialPositionKura;
    void znakpomocy();
    void switchTofarm();
    void handleEvents();
    void render();
    void switchplace();
    void addToPasek();
    void renderTopasek();
    void addstorage();
    void dodajzwierzeta();
    void krowachodzi();
    void update();
    void deadanimals();
    void updateCowMovementKrowa();
    void updateCowMovementSwinia();
    void updateCowMovementKura();
    void loadtimes();
    void savetimeall();
    void saveTimeToFile();
    void loadTimeFromFile();
    void addhelp();
    void addpadlock();
    void zyjeczynie();
};
