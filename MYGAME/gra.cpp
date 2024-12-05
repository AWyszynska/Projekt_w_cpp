
#include "gra.h"
#include "guzik.h" 
#include <iostream>
#include <SFML/Graphics.hpp>
#include "garden.h"
#include "shop.h"

Game::Game(sf::RenderWindow& window): window(window),isRunning(true),
zlotowkiFile("zlotowki_value.txt"),
ogrod(window, sf::Vector2f(60, 195), sf::Vector2f(332, 245)),//za pomocą klasy tworzącej guziki tworze miejsca 
sad(window, sf::Vector2f(400, 200), sf::Vector2f(335, 340)),
kopalnia(window, sf::Vector2f(50, 479), sf::Vector2f(638, 321)),
hodowla(window, sf::Vector2f(815, 75), sf::Vector2f(340, 339)),
sklep(window, sf::Vector2f(845, 480), sf::Vector2f(340, 339)),
openall(nullptr)
{
    window.setFramerateLimit(60);
 if (!font.loadFromFile("Flottflott.ttf")) {
            std::cout << "Error loading font file!" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
 zlotowkiText.setFont(font);
    zlotowkiText.setCharacterSize(30);
    zlotowkiText.setFillColor(sf::Color::Black);
    zlotowkiText.setPosition(1000, 90); 
    zlotowkiText.setString("Zlotowki: " + std::to_string(zlotowkiValue));

    if (zlotowkiFile.is_open()) {
        zlotowkiFile >> zlotowkiValue;
        zlotowkiFile.close();
    }
   


    if (!backgroundTexture.loadFromFile("aazdj/tlopoprawione.png")) {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    background.setTexture(backgroundTexture);
    if (!pasek_zdj.loadFromFile("aazdj/pasek.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    pasek.setTexture(pasek_zdj);
    pasek.setPosition(260.0f, 680.0f);
    pasek.setScale(0.9f, 0.9f);
    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png")) {
    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);




}

void Game::run()
{
     renderTopasek();
      openall = new Openall(window, ReadSigns, Readvalues);
          if(!ReadSigns.empty()){
    hoverDisplay = new HoverDisplays(window,ReadSigns[0],270,400,690,790);
    hoverDisplay2 = new HoverDisplays(window,ReadSigns[1],410,530,690,790);
    hoverDisplay3 = new HoverDisplays(window,ReadSigns[2],540,670,690,790);
    hoverDisplay4 = new HoverDisplays(window,ReadSigns[3],670,800,690,790);
    }
    while (window.isOpen()) {
        handleEvents();
        render();
        loadedplace();

    }
}
//dodaje zdjęcia do struktur
void Game::loadedplace()
{
        if (!guzikTexture.loadFromFile("aazdj/ggg.png")) {
        std::cout<<"blad\n";
    }
    ogrod.setTexture(guzikTexture);

        if (!sadzdjecie.loadFromFile("aazdj/sad1.png")) {
        std::cout<<"blad\n";
   }
   sad.setTexture(sadzdjecie);

        if (!cavephoto.loadFromFile("aazdj/kopalnia1.png")) {
        std::cout<<"blad\n";
    }
    kopalnia.setTexture(cavephoto);
        if (!animalphoto.loadFromFile("aazdj/hodowla1.png")) {
        std::cout<<"blad\n";
    }
    hodowla.setTexture(animalphoto);
    if (!shopphoto.loadFromFile("aazdj/sklep1.png")) {
        std::cout<<"blad\n";
    }
    sklep.setTexture(shopphoto);
}

void Game::renderTopasek(){
    std::ifstream file("wypisz_values.txt");
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (file >> Signs) {
        if (Signs != ' ') {
            ReadSigns.push_back(Signs);
        }
    }
  file.close();        

        std::ifstream files("letter_values.txt");
    if (!files.is_open()) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (files >> valuess) {
        if (valuess != ' ') {
           Readvalues.push_back(valuess);
        }
    }
  files.close(); 
}
//generuje wartości na pasku na dole
void Game::addToPasek(){
int position = 270;
    int interval = 150;
int displayedValues = 0;
int displayedVal = 0;
   // sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    //hoverDisplay.displayImageOnHover(mousePosition);
    int numIterations = std::min(static_cast<int>(ReadSigns.size()), 4);
    for (int i = 0; i < numIterations; i++ ) {
        if (displayedValues >= 4) {
            break; 
        }
        if (ReadSigns[i] == 'P') {
           
            if (obraz1.loadFromFile("aazdj/nasiono1.png")) {
                sf::Sprite sprite(obraz1);
                sprite.setPosition(position,700); 
                sprite.setScale(0.15f, 0.15f);
                window.draw(sprite);
                displayedValues++;
                
            }
        } else if (ReadSigns[i] == 'M') {
           
            if (obraz2.loadFromFile("aazdj/nasionamarchewka.png")) {
                sf::Sprite sprite(obraz2);
                sprite.setPosition(position,700); 
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
                displayedValues++;
            }
        } else if (ReadSigns[i] == 'T') {

            if (obraz3.loadFromFile("aazdj/nasionatruskawka.png")) {
                sf::Sprite sprite(obraz3);
                sprite.setPosition(position + 10,700); 
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
                displayedValues++;
            }
        }
                else if (ReadSigns[i] == 'C') {

            if (carrottolinephoto.loadFromFile("aazdj/carrot.png")) {
                //sf::Sprite sprite3(obraz3);
               carrottoline.setTexture(carrottolinephoto);
                carrottoline.setPosition(position - 5 ,700); 
                carrottoline.setScale(0.25f, 0.25f);
                window.draw(carrottoline);
                displayedValues++;


            }
        }
        else if (ReadSigns[i] == 'S') {

            if (strawberrytolinephoto.loadFromFile("aazdj/truskawka.png")) {
                //sf::Sprite sprite3(obraz3);
                strawberrytoline.setTexture(strawberrytolinephoto);
                strawberrytoline.setPosition(position - 10,700); 
                strawberrytoline.setScale(0.3f, 0.3f);
                window.draw(strawberrytoline);
                displayedValues++;


            }
        }
        else if (ReadSigns[i] == 'J') {

            if (obraz4.loadFromFile("zdjeciasad/nasionajablka.png")) {
                sf::Sprite sprite(obraz4);
                sprite.setPosition(position,690); 
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'G') {

            if (obraz5.loadFromFile("zdjeciasad/nasionagruszki.png")) {
                 sf::Sprite sprite(obraz5);
                sprite.setPosition(position,690); 
                sprite.setScale(0.35f, 0.35f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'Z') {

            if (obraz6.loadFromFile("zdjeciasad/nasionkosliwa.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position,690); 
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
                displayedValues++;
            }
        }
                else if (ReadSigns[i] == 'A') {//F

            if (obraz7.loadFromFile("zdjeciasad/jablkozdjecie.png")) {
                sf::Sprite sprite(obraz7);
                sprite.setPosition(position,690); 
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'E') {//gruszka

            if (obraz8.loadFromFile("zdjeciasad/gruszkazdjecie.png")) {
                sf::Sprite sprite(obraz8);
                sprite.setPosition(position,690); 
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'F') {//sliwka

            if (obraz9.loadFromFile("zdjeciasad/sliwkazdjecie.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position+10,690); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'I') {//miedz

            if (obraz9.loadFromFile("kopalnia/sztabkamiedz.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'R') {//srebro

            if (obraz9.loadFromFile("kopalnia/sztabkasrebro.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'L') {//zloto

            if (obraz9.loadFromFile("kopalnia/sztabkazloto.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'D') {//diament

            if (obraz9.loadFromFile("kopalnia/diament.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position-10,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'W') {

            if (obraz9.loadFromFile("hodowlazdj/jajkoswinka.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'K') {

            if (obraz9.loadFromFile("hodowlazdj/jajkokrowka.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'U') {

            if (obraz9.loadFromFile("hodowlazdj/jajkokura.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        position += interval;
    }
            xPos = 220;
        for (int i = 0; i <numIterations; ++i) {
            xPos += 140;
             if (Readvalues[i] != 0) { 
            text.setString(std::to_string(Readvalues[i]));
            text.setPosition(xPos, 750); 
            window.draw(text);
         }
        }




}


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
                window.close();
            } 
    else if (event.type == sf::Event::MouseButtonPressed) {
        if(openwerehouse){

        openall->handleMouseEvent(event);
            ReadSigns = openall->getCharValues();
            Readvalues = openall->getIntValues();
        }
             }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                clickPosition = sf::Mouse::getPosition(window);
                //std::cout << "x: " << clickPosition.x << " y: " << clickPosition.y << std::endl;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
            // jeśli naciśniesz na dane miejsca przekierowuje Cię do niego
            if (ogrod.isHoveredButton()) {
                switchToGarden();
            }
            if (sklep.isHoveredButton()) {
                switchToShop();
            }
             if (sad.isHoveredButton()) {
                switchToOrchard();
            }
            if (kopalnia.isHoveredButton()) {
                switchToCave();
            }
            if (hodowla.isHoveredButton()) {
                switchToHodowla();
            }
            if(points.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
        openwerehouse = !openwerehouse;
        sorrywiondowisopen = !sorrywiondowisopen;
    }
        }
    }
}

void Game::addstorage(){
    if (!pointsphoto.loadFromFile("aazdj/kropki.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    points.setTexture(pointsphoto);
    points.setPosition(830.0f, 725.0f);
    points.setScale(0.4f, 0.4f);
    window.draw(points);
}

void Game::render()
{
        window.clear();
        window.draw(background);
        ogrod.handleMouseInteraction();
        ogrod.draw();
        sad.handleMouseInteraction();
        sad.draw();
        kopalnia.handleMouseInteraction();
        kopalnia.draw();
        hodowla.handleMouseInteraction();
        hodowla.draw();
        sklep.handleMouseInteraction();
        sklep.draw();
        hodowla.handleMouseInteraction();
        hodowla.draw();
        window.draw(pasek);
        window.draw(skrzynka);
        std::ifstream zlotowkiFile("zlotowki_value.txt");
   addToPasek();


zlotowkiText.setString(std::to_string(zlotowkiValue));
    window.draw(zlotowkiText);


   



       addstorage();
           if(!ReadSigns.empty()){
    hoverDisplay->update();
    hoverDisplay2->update();
    hoverDisplay3->update();
    hoverDisplay4->update();
    }
        window.display();
}


void Game::switchToGarden() {

    Garden garden(window);
    garden.run();
}

void Game::switchToShop() {

    Shop shop(window);
    shop.run();
}

void Game::switchToOrchard() {

    Orchard orchard(window);
    orchard.run();
}

void Game::switchToCave() {

    Cave cave(window);
    cave.run();
}

void Game::switchToHodowla() {

    Hodowla hodowla(window);
    hodowla.run();
}

Game::~Game() {
    delete openall;
    delete hoverDisplay;
    delete hoverDisplay2;
    delete hoverDisplay3;
    delete hoverDisplay4;
}


































