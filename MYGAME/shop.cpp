#include "shop.h" 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <sstream>

Shop::Shop(sf::RenderWindow& window) : window(window),
    buykernel1(window, sf::Vector2f(210, 210), sf::Vector2f(100, 100)),//klasa ktora generuje rzeczy do kupienia
    buykernel2(window, sf::Vector2f(376, 210), sf::Vector2f(100, 100)),
    buykernel3(window, sf::Vector2f(542, 210), sf::Vector2f(100, 100)),
    buykernel4(window, sf::Vector2f(712, 210), sf::Vector2f(100, 100)),
    buykernel5(window, sf::Vector2f(878, 210), sf::Vector2f(100, 100)),
    buykernel6(window, sf::Vector2f(195, 360), sf::Vector2f(100, 100)),
    buykernel7(window, sf::Vector2f(386, 360), sf::Vector2f(70, 100)),
    buykernel8(window, sf::Vector2f(552, 360), sf::Vector2f(70, 100)),
    buykernel9(window, sf::Vector2f(722, 360), sf::Vector2f(70, 100)),
    exit(window, sf::Vector2f(50, 50), sf::Vector2f(100, 100)),
    isRunning(true),zlotowki(10000000),showLowMoneyMessage(false),
    pieniadze(sf::Text("", font, 30)),openall(nullptr) {
    window.setFramerateLimit(60);


//tło
    if (!backgroundTexture.loadFromFile("aazdj/sklepzdj.png")) {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    background.setTexture(backgroundTexture);
  //czcionka
        if (!font.loadFromFile("Flottflott.ttf")) {
            std::cout << "Error loading font file!" << std::endl;
        }
         else{
            std::cout << "działa" << std::endl;
        }
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

if (!exittextur.loadFromFile("aazdj/wyjscie.png")) {
        std::cout<<"blad\n";
   }
   exit.setTexture(exittextur);

        pieniadze.setFont(font);
        pieniadze.setCharacterSize(30);
        pieniadze.setFillColor(sf::Color::Black);

    ss << zlotowki; // Inicjalizacja ss
    zlotowkiStr = ss.str();
    
}
//dodaje wartości do klasy wypisz żeby potem dać je na dole strony
void Shop::renderTopasek(){
    std::ifstream file("wypisz_values.txt");
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (file >> Signs) {
        if (Signs != ' ') {
            wypisz.push_back(Signs);
        }
    }
  file.close();        

        std::ifstream files("letter_values.txt");
    if (!files.is_open()) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (files >> valuess) {
        if (valuess != ' ') {
           letter.push_back(valuess);
        }
    }
  files.close(); 
}


//dodaje cenówki, pasek i skrzynkę
void Shop::addprice(){
    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png")) {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);

    if (!pasek_zdj.loadFromFile("aazdj/pasek.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    pasek.setTexture(pasek_zdj);
    pasek.setPosition(260.0f, 680.0f);
    pasek.setScale(0.9f, 0.9f);

    if (!pricesset1.loadFromFile("aazdj/pszencena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price1.setTexture(pricesset1);
    price1.setPosition(164.0f, 270.0f);
    price1.setScale(0.5f, 0.5f);

    if(!pricesset2.loadFromFile("aazdj/marcena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price2.setTexture(pricesset2);
    price2.setPosition(334.0f, 270.0f);
    price2.setScale(0.5f, 0.5f);

    if(!pricesset3.loadFromFile("aazdj/truskcena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price3.setTexture(pricesset3);
    price3.setPosition(504.0f, 270.0f);
    price3.setScale(0.5f, 0.5f);

    if (!pricesset4.loadFromFile("zdjeciasad/jablkacena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price4.setTexture(pricesset4);
    price4.setPosition(674.0f, 270.0f);
    price4.setScale(0.5f, 0.5f);

    if(!pricesset5.loadFromFile("zdjeciasad/gruszkacena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price5.setTexture(pricesset5);
    price5.setPosition(844.0f, 270.0f);
    price5.setScale(0.5f, 0.5f);

    if(!pricesset6.loadFromFile("zdjeciasad/sliwkacena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price6.setTexture(pricesset6);
    price6.setPosition(164.0f, 420.0f);
    price6.setScale(0.5f, 0.5f);
    if(!pricesset7.loadFromFile("aazdj/swiniajajkocena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
        price7.setTexture(pricesset7);
    price7.setPosition(334.0f, 420.0f);
    price7.setScale(0.5f, 0.5f);
        if(!pricesset8.loadFromFile("aazdj/krowajajkocena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price8.setTexture(pricesset8);
    price8.setPosition(504.0f, 420.0f);
    price8.setScale(0.5f, 0.5f);
        if(!pricesset9.loadFromFile("aazdj/kurajajkocena.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    price9.setTexture(pricesset9);
    price9.setPosition(674.0f,420.0f);
    price9.setScale(0.5f, 0.5f);
}
//totaje tekstury do odpowiednich struktur 
void Shop::addkernalforshelf(){
    if (!ziar1.loadFromFile("aazdj/nasiono1.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel1.setTexture(ziar1);
    if (!ziar2.loadFromFile("aazdj/nasionamarchewka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel2.setTexture(ziar2);
    if (!ziar3.loadFromFile("aazdj/nasionatruskawka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel3.setTexture(ziar3);

    if (!ziar4.loadFromFile("zdjeciasad/nasionajablka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel4.setTexture(ziar4);
    if (!ziar5.loadFromFile("zdjeciasad/nasionagruszki.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel5.setTexture(ziar5);
    if (!ziar6.loadFromFile("zdjeciasad/nasionkosliwa.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel6.setTexture(ziar6);
        if (!ziar7.loadFromFile("hodowlazdj/jajkoswinka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel7.setTexture(ziar7);
        if (!ziar8.loadFromFile("hodowlazdj/jajkokrowka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel8.setTexture(ziar8);
        if (!ziar9.loadFromFile("hodowlazdj/jajkokura.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    buykernel9.setTexture(ziar9);
}


void Shop::run() {
    renderTopasek();
    openall = new Openall(window, wypisz, letter);
        if(!wypisz.empty()){
    hoverDisplay = new HoverDisplays(window,wypisz[0],270,400,690,790);
    hoverDisplay2 = new HoverDisplays(window,wypisz[1],410,530,690,790);
    hoverDisplay3 = new HoverDisplays(window,wypisz[2],540,670,690,790);
    hoverDisplay4 = new HoverDisplays(window,wypisz[3],670,800,690,790);
    }
    while (window.isOpen()) {
        handleEvents();
        addprice();
        render();
        addkernalforshelf();

    }
}
void Shop::addstorage(){
    if (!pointsphoto.loadFromFile("aazdj/kropki.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    points.setTexture(pointsphoto);
    points.setPosition(830.0f, 725.0f);
    points.setScale(0.4f, 0.4f);
    window.draw(points);
}
void Shop::handleEvents() {
    sf::Event event;
    ValueHandler valueHandler(window, wypisz, letter, zlotowki);//klasa ktora sprzedaje rzeczy
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
                    std::ofstream wypiszFile("wypisz_values.txt");
    if (wypiszFile.is_open()) {
        for (char znak : wypisz) {
            wypiszFile << znak << " ";
        }
        wypiszFile.close();
    }
    std::ofstream letterFile("letter_values.txt");
    if (letterFile.is_open()) {
        for (int value : letter) {
            letterFile << value << " ";
        }
        letterFile.close();
    }
    std::ofstream zlotowkiFile("zlotowki_value.txt");
    if (zlotowkiFile.is_open()) {
        zlotowkiFile << zlotowki;
        zlotowkiFile.close();
    }
            window.close();
            }

                    else if (event.type == sf::Event::MouseButtonPressed) {
        if(openwerehouse){

        openall->handleMouseEvent(event);
            wypisz = openall->getCharValues();
           letter = openall->getIntValues();
        }
             }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);

            valueHandler.handleRightClick(mousePos);
                        std::stringstream ss;
            ss << zlotowki;
            zlotowkiStr = ss.str();
        }
         else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
            if (exit.isHoveredButton()) {
                switchTofarm();
            }

    if(points.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
        openwerehouse = !openwerehouse;
        sorrywiondowisopen = !sorrywiondowisopen;
    }
            else if(znakzapytania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                pomocotwarta = true;
                
            }  
            else if(wyjscietablica.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                    pomocotwarta = false;
                } 
                // gdy gdy kupujesz coś do zmiejsza się cena i dodaje do wektora wypisz
            if (buykernel1.isHoveredButton()) {//pszenica
                         if (zlotowki >= 10) {
                    zlotowki -= 10;
                     showLowMoneyMessage = false;
                ss.str(""); 
                ss << zlotowki; 
                zlotowkiStr = ss.str();


        }
        else {
                    showLowMoneyMessage = true; 
                }
            if(!showLowMoneyMessage){    
                 licznik = 0;   
                  found = false;
                  char znak = 'P';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back('P');
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == 'P'){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 

            }
            }
            else if (buykernel2.isHoveredButton()) {//marchewka
                licznik = 0;   
                        if (zlotowki >= 50) {
                    zlotowki -= 50;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
                     if(!showLowMoneyMessage){
                  found = false;
                  char znak = 'M';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back('M');
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == 'M'){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
                     }

 
            }


            else if (buykernel3.isHoveredButton()) {//truskawka
              licznik = 0;   
                      if (zlotowki >= 120) {
                    zlotowki -= 120;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
                if(!showLowMoneyMessage){     
                  found = false;
                  char znak = 'T';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(truskawkaznak);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == truskawkaznak){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
        }
            }



                    else if (buykernel4.isHoveredButton()) {//marchewka
              licznik = 0;   
                      if (zlotowki >= 300) {
                    zlotowki -= 300;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
                     if(!showLowMoneyMessage){
                  found = false;
                  char znak = 'J';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(jablkoznak);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == jablkoznak){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
                     }

            }
    else if (buykernel5.isHoveredButton()) {//marchewka
              licznik = 0;   
                      if (zlotowki >= 500) {
                    zlotowki -= 500;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
               if(!showLowMoneyMessage){      
                  found = false;
                  char znak = 'G';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(gruszkaznak);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == gruszkaznak){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
               }

            }
    else if (buykernel6.isHoveredButton()) {
 licznik = 0;   
         if (zlotowki >= 700) {
                    zlotowki -= 700;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
if(!showLowMoneyMessage){ 
                  found = false;
                  char znak = 'Z';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(sliwkaznak);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == sliwkaznak){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
}

 
            }
            else if (buykernel7.isHoveredButton()) {
 licznik = 0;   
         if (zlotowki >= 100000) {
                    zlotowki -= 100000;
                    showLowMoneyMessage = false;
                    ss.str(""); 
                    ss << zlotowki; 
                    zlotowkiStr = ss.str();

        }else {
                    showLowMoneyMessage = true; 
                     }
             if(!showLowMoneyMessage){ 
                  found = false;
                  char znak = 'W';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(jajkoswinia);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == jajkoswinia){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
             }

 
            }

else if (buykernel8.isHoveredButton()) {
 licznik = 0;  

         if (zlotowki >= 200000) {
                    zlotowki -= 200000;
                    showLowMoneyMessage = false;
                ss.str(""); 
                ss << zlotowki; 
                zlotowkiStr = ss.str();
                     }else {
                    showLowMoneyMessage = true; 
                     }


             if(!showLowMoneyMessage){ 
                  found = false;
                  char znak = 'K';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }
            if(!found){
                
                wypisz.push_back(jajkokrowa);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == jajkokrowa){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
 }
 

 
            }
    else if (buykernel9.isHoveredButton()) {
 licznik = 0; 
         if (zlotowki >= 300000) {
                    zlotowki -= 300000;
                    showLowMoneyMessage = false;
                ss.str("");
                ss << zlotowki;
                zlotowkiStr = ss.str();
            } else {
                showLowMoneyMessage = true;
            }  
 if(!showLowMoneyMessage){
                  found = false;
                  char znak = 'U';
        for(int j = 0;j < wypisz.size(); j++){
            if(wypisz[j] == znak){
                
                letter[j] += 1;
                found = true;
                
                break;
            }
        }

            if(!found){
                
                wypisz.push_back(jajkokura);
                letter.push_back(0);
                for(int j = 0;j < wypisz.size(); j++){
                    if(wypisz[j] == jajkokura){
                        letter[j] += 1;
                        break;
                    }
                }            
            } 
 }

}


        }
    }
}
//dodaje wartości do paska na dole ,,generuje"
void Shop::tableforunder(){

        int position = 270;
    int interval = 150;
 int numIterations = std::min(static_cast<int>(wypisz.size()), 4);
    for (int i = 0; i < numIterations; i++ ) {
        if (wypisz[i] == 'P') {
           
            if (obraz1.loadFromFile("aazdj/nasiono1.png")) {
                sf::Sprite sprite(obraz1);
                sprite.setPosition(position,690); 
                sprite.setScale(0.15f, 0.15f);
                window.draw(sprite);
                
            }
        } else if (wypisz[i] == 'M') {
           
            if (obraz2.loadFromFile("aazdj/nasionamarchewka.png")) {
                sf::Sprite sprite(obraz2);
                sprite.setPosition(position,700); 
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
            }
        } else if (wypisz[i] == 'T') {

            if (obraz3.loadFromFile("aazdj/nasionatruskawka.png")) {
                sf::Sprite sprite(obraz3);
                sprite.setPosition(position,690); 
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
            }
        }else if (wypisz[i] == 'J') {

            if (obraz4.loadFromFile("zdjeciasad/nasionajablka.png")) {
                sf::Sprite sprite(obraz4);
                sprite.setPosition(position,690); 
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
            }
        }else if (wypisz[i] == 'G') {

            if (obraz5.loadFromFile("zdjeciasad/nasionagruszki.png")) {
                sf::Sprite sprite(obraz5);
                sprite.setPosition(position,690); 
                sprite.setScale(0.35f, 0.35f);
                window.draw(sprite);
            }
        }else if (wypisz[i] == 'Z') {

            if (obraz6.loadFromFile("zdjeciasad/nasionkosliwa.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position,690); 
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
            }
        }else if (wypisz[i] == 'W') {

            if (obraz6.loadFromFile("hodowlazdj/jajkoswinka.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        else if (wypisz[i] == 'K') {

            if (obraz6.loadFromFile("hodowlazdj/jajkokrowka.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        else if (wypisz[i] == 'U') {

            if (obraz6.loadFromFile("hodowlazdj/jajkokura.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position,690); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        else if (wypisz[i] == 'C') {

            if (obraz6.loadFromFile("aazdj/carrot.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position - 5 ,700); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);


            }
        }
        else if (wypisz[i] == 'S') {

            if (obraz6.loadFromFile("aazdj/truskawka.png")) {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position - 10,700); 
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);


            }
        }
            else if (wypisz[i] == 'A') {//F

            if (obraz7.loadFromFile("zdjeciasad/jablkozdjecie.png")) {
                sf::Sprite sprite(obraz7);
                sprite.setPosition(position,690); 
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);

            }
        }
        else if (wypisz[i] == 'E') {//gruszka

            if (obraz8.loadFromFile("zdjeciasad/gruszkazdjecie.png")) {
                sf::Sprite sprite(obraz8);
                sprite.setPosition(position,690); 
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);

            }
        }
        else if (wypisz[i] == 'F') {//sliwka

            if (obraz9.loadFromFile("zdjeciasad/sliwkazdjecie.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position+10,690); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);

            }
            }else if (wypisz[i] == 'I') {//miedz

            if (obraz9.loadFromFile("kopalnia/sztabkamiedz.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);

            }
        }
        else if (wypisz[i]== 'R') {//srebro

            if (obraz9.loadFromFile("kopalnia/sztabkasrebro.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);

            }
        }
        else if (wypisz[i] == 'L') {//zloto

            if (obraz9.loadFromFile("kopalnia/sztabkazloto.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);

            }
        }
        else if (wypisz[i] == 'D') {//diament

            if (obraz9.loadFromFile("kopalnia/diament.png")) {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position-10,720); 
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);

            }
        }
        position += interval;
    }
 xPos = 220;
        for (int i = 0; i < numIterations; ++i) {
            xPos += 140;
             if (letter[i] != 0) { 
            text.setString(std::to_string(letter[i]));
            text.setPosition(xPos, 750);
            window.draw(text);
         }
        }



}
void Shop::addhelp(){
    if (!zapytaniezdj.loadFromFile("znakzapytania/zapytanie2.png")) {
    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    znakzapytania.setTexture(zapytaniezdj);
    znakzapytania.setPosition(1080.0f, 660.0f);
    znakzapytania.setScale(0.2f, 0.2f);
}
void Shop::znakpomocy(){
    if (!tablicapomoczdj.loadFromFile("znakzapytania/skleptablica.png")) {
    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    tablicapomoc.setTexture(tablicapomoczdj);
    tablicapomoc.setPosition(50.0f, 0.0f);
    tablicapomoc.setScale(0.9f, 0.9f);
    wyjscietablica.setTexture(exittextur);
    wyjscietablica.setPosition(900.0f, 100.0f);
    wyjscietablica.setScale(0.3f, 0.3f);
    window.draw(tablicapomoc);
    window.draw(wyjscietablica);
}
void Shop::render()
{
        window.clear();
        
        window.draw(background);
        window.draw(pasek);
        buykernel1.handleMouseInteraction();
        buykernel1.draw();
        buykernel2.handleMouseInteraction();
        buykernel2.draw();
        buykernel3.handleMouseInteraction();
        buykernel3.draw();

        buykernel4.handleMouseInteraction();
        buykernel4.draw();
        buykernel5.handleMouseInteraction();
        buykernel5.draw();
        buykernel6.handleMouseInteraction();
        buykernel6.draw();
        buykernel7.handleMouseInteraction();
        buykernel7.draw();
        buykernel8.handleMouseInteraction();
        buykernel8.draw();
        buykernel9.handleMouseInteraction();
        buykernel9.draw();
        exit.handleMouseInteraction();
        exit.draw();
        window.draw(price1);
        window.draw(price2);
        window.draw(price3);
        window.draw(price4);
        window.draw(price5);
        window.draw(price6);
        window.draw(price7);
        window.draw(price8);
        window.draw(price9);
       
        
         window.draw(skrzynka);
       
pieniadze.setString(zlotowkiStr);
pieniadze.setPosition(1000, 90);
window.draw(pieniadze);

window.draw(points);
    if (showLowMoneyMessage) {
        sf::Text lowMoneyMessage;
        lowMoneyMessage.setFont(font); //jeśni nie będzie cię stać tutaj jest strzeżenie 
        lowMoneyMessage.setString("Masz za malo pieniedzy aby to kupic");
        lowMoneyMessage.setCharacterSize(30); 
        lowMoneyMessage.setFillColor(sf::Color::Red); 
        lowMoneyMessage.setPosition(window.getSize().x / 2 - lowMoneyMessage.getLocalBounds().width / 2, 600);
            if(!wypisz.empty()){
    hoverDisplay->update();
    hoverDisplay2->update();
    hoverDisplay3->update();
    hoverDisplay4->update();
    }
        window.draw(lowMoneyMessage);
    }
    addstorage();
     if (!openwerehouse) {
        tableforunder();
    } else {

            openall->drawtank();
            openall->addsToPasek();
        
    }
    addhelp();
    if(pomocotwarta){
    znakpomocy();
        }
    window.draw(znakzapytania);
 window.display();
}

void Shop::switchTofarm() {

        std::ofstream wypiszFile("wypisz_values.txt");
    if (wypiszFile.is_open()) {
        for (char znak : wypisz) {
            wypiszFile << znak << " ";
        }
        wypiszFile.close();
    }
    std::ofstream letterFile("letter_values.txt");
    if (letterFile.is_open()) {
        for (int value : letter) {
            letterFile << value << " ";
        }
        letterFile.close();
    }
    std::ofstream zlotowkiFile("zlotowki_value.txt");
    if (zlotowkiFile.is_open()) {
        zlotowkiFile << zlotowki;
        zlotowkiFile.close();
    }

    Game game(window);
    game.run();
}
Shop::~Shop() {
    delete openall;
    delete hoverDisplay;
    delete hoverDisplay2;
    delete hoverDisplay3;
    delete hoverDisplay4;
}