
#include "openall.h" 

Openall::Openall(sf::RenderWindow& window,std::vector<char>& charvalues,std::vector<int>& intvalues)
 : window(window), charvalues(charvalues), intvalues(intvalues), firstItemSelected(false) {
    
}
void Openall::drawtank(){
    //for(int i =0;i<charvalues.size();i++){
        //std::cout<<charvalues[i];
    //}
             sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //hoverDisplay.displayImageOnHover(mousePosition);
if (!werehousephoto.loadFromFile("aazdj/magazynn.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    werehouse.setTexture(werehousephoto);
    werehouse.setPosition(100.0f, 50.0f);
    werehouse.setScale(0.8f, 0.8f);
    window.draw(werehouse);
    //for (int i = 0; i < charvalues.size(); i++ ) {
    //std::cout<<intvalues[i]<<std::endl;
    //}
         if (!font.loadFromFile("Flottflott.ttf")) {
            std::cout << "Error loading font file!" << std::endl;
        }
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

    

}
void Openall::addsToPasek(){
    position = 260;
    int interval = 160;
    int displayedValues = 0;
    int displayedVal = 0;
    int itemCounter = 0; 
    float odleglosc = 700.f;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    //hoverDisplay.displayImageOnHover(mousePosition);
     for (int i = 0; i < charvalues.size(); i++ ) {
        itemCounter++;

        if (itemCounter == 5) {
            odleglosc = 125;
            position = 200; // Change distance

        }
        if (itemCounter == 10) {
            odleglosc = 230;
            position = 200; // Change distance

        }
        if (charvalues[i] == 'P' ) {
           
            if (obraz1.loadFromFile("aazdj/nasiono1.png")) {

                sprite1.setTexture(obraz1);
                //sf::Sprite sprite1(obraz1);
    sprite1.setPosition(position,odleglosc); 
                sprite1.setScale(0.15f, 0.15f);
                window.draw(sprite1);

            }
        } else if (charvalues[i] == 'M') {
           
            if (obraz2.loadFromFile("aazdj/nasionamarchewka.png")) {
                //sf::Sprite sprite2(obraz2);
                sprite2.setTexture(obraz2);
                sprite2.setPosition(position,odleglosc); 
                sprite2.setScale(0.7f, 0.7f);
                window.draw(sprite2);
            }
        } else if (charvalues[i] == 'T') {

            if (obraz3.loadFromFile("aazdj/nasionatruskawka.png")) {
                //sf::Sprite sprite3(obraz3);
                sprite3.setTexture(obraz3);
                sprite3.setPosition(position + 10,odleglosc); 
                sprite3.setScale(0.7f, 0.7f);
                window.draw(sprite3);

            }
        }
        else if (charvalues[i] == 'C') {

            if (carrottolinephoto.loadFromFile("aazdj/carrot.png")) {
                //sf::Sprite sprite3(obraz3);
               carrottoline.setTexture(carrottolinephoto);
                carrottoline.setPosition(position - 5 ,odleglosc); 
                carrottoline.setScale(0.25f, 0.25f);
                window.draw(carrottoline);


            }
        }
        else if (charvalues[i] == 'S') {

            if (strawberrytolinephoto.loadFromFile("aazdj/truskawka.png")) {
                //sf::Sprite sprite3(obraz3);
                strawberrytoline.setTexture(strawberrytolinephoto);
                strawberrytoline.setPosition(position - 10,odleglosc); 
                strawberrytoline.setScale(0.3f, 0.3f);
                window.draw(strawberrytoline);


            }
        }
        else if (charvalues[i] == 'J') {

            if (obraz4.loadFromFile("zdjeciasad/nasionajablka.png")) {
                sprite4.setTexture(obraz4);
                sprite4.setPosition(position,odleglosc); 
                sprite4.setScale(0.4f, 0.4f);
                window.draw(sprite4);

            }
        }
        else if (charvalues[i] == 'G') {

            if (obraz5.loadFromFile("zdjeciasad/nasionagruszki.png")) {
                 sprite5.setTexture(obraz5);
                sprite5.setPosition(position,odleglosc); 
                sprite5.setScale(0.35f, 0.35f);
                window.draw(sprite5);

            }
        }
        else if (charvalues[i] == 'Z') {

            if (obraz6.loadFromFile("zdjeciasad/nasionkosliwa.png")) {
                sprite6.setTexture(obraz6);
                sprite6.setPosition(position,odleglosc); 
                sprite6.setScale(0.4f, 0.4f);
                window.draw(sprite6);

            }
        }
        else if (charvalues[i] == 'A') {//F

            if (obraz7.loadFromFile("zdjeciasad/jablkozdjecie.png")) {
                sprite7.setTexture(obraz7);
                sprite7.setPosition(position,odleglosc); 
                sprite7.setScale(0.2f, 0.2f);
                window.draw(sprite7);
                displayedValues++;
            }
        }
        else if (charvalues[i] == 'E') {//gruszka

            if (obraz8.loadFromFile("zdjeciasad/gruszkazdjecie.png")) {
                sprite8.setTexture(obraz8);
                sprite8.setPosition(position,odleglosc); 
                sprite8.setScale(0.2f, 0.2f);
                window.draw(sprite8);
                displayedValues++;
            }
        }
        else if (charvalues[i] == 'F') {//sliwka

            if (obraz9.loadFromFile("zdjeciasad/sliwkazdjecie.png")) {
                sprite9.setTexture(obraz9);
                sprite9.setPosition(position+10,odleglosc); 
                sprite9.setScale(0.25f, 0.25f);
                window.draw(sprite9);
                displayedValues++;
            }
            }else if (charvalues[i] == 'I') {//miedz

            if (obraz10.loadFromFile("kopalnia/sztabkamiedz.png")) {
                sprite10.setTexture(obraz10);
                sprite10.setPosition(position,odleglosc); 
                sprite10.setScale(0.25f, 0.25f);
                window.draw(sprite10);
                displayedValues++;
            }
        }
        else if (charvalues[i]== 'R') {//srebro

            if (obraz11.loadFromFile("kopalnia/sztabkasrebro.png")) {
                sprite11.setTexture(obraz11);
                sprite11.setPosition(position,odleglosc); 
                sprite11.setScale(0.25f, 0.25f);
                window.draw(sprite11);
                displayedValues++;
            }
        }
        else if (charvalues[i] == 'L') {//zloto

            if (obraz12.loadFromFile("kopalnia/sztabkazloto.png")) {
                sprite12.setTexture(obraz12);
                sprite12.setPosition(position,odleglosc); 
                sprite12.setScale(0.25f, 0.25f);
                window.draw(sprite12);
                displayedValues++;
            }
        }
        else if (charvalues[i] == 'D') {//diament

            if (obraz13.loadFromFile("kopalnia/diament.png")) {
                sprite13.setTexture(obraz13);
                sprite13.setPosition(position-10,odleglosc); 
                sprite13.setScale(0.25f, 0.25f);
                window.draw(sprite13);
                displayedValues++;
            }
        }
        else if (charvalues[i] == 'W') {

            if (obraz14.loadFromFile("hodowlazdj/jajkoswinka.png")) {
                sprite14.setTexture(obraz14);
                sprite14.setPosition(position,odleglosc); 
                sprite14.setScale(0.3f, 0.3f);
                window.draw(sprite14);
            }
        }
        else if (charvalues[i] == 'K') {

            if (obraz15.loadFromFile("hodowlazdj/jajkokrowka.png")) {
                sprite15.setTexture(obraz15);
                sprite15.setPosition(position,odleglosc); 
                sprite15.setScale(0.3f, 0.3f);
                window.draw(sprite15);
            }
        }
        else if (charvalues[i] == 'U') {

            if (obraz16.loadFromFile("hodowlazdj/jajkokura.png")) {
                sprite16.setTexture(obraz16);
                sprite16.setPosition(position,odleglosc); 
                sprite16.setScale(0.3f, 0.3f);
                window.draw(sprite16);
            }
        }
        position += interval;
    }
            xPos = 220;
            int liczbyCounter = 0; 
            float positionsvalues = 760;
        for (int i = 0; i < intvalues.size(); ++i) {
        liczbyCounter++;
        if (liczbyCounter == 5) {
            xPos = 110;
            positionsvalues = 180;

        }
        if (liczbyCounter == 10) {
            xPos = 110;
            positionsvalues = 295; 

        }
        xPos += 140;
         if (intvalues[i] != 0) { 
            text.setString(std::to_string(intvalues[i]));
            text.setPosition(xPos, positionsvalues); 
            window.draw(text);
         }
        }

}

void Openall::handleMouseEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        checkForItemSelection(mousePos);
    }
}


void Openall::checkForItemSelection(const sf::Vector2f& mousePos) {
    for (char item : charvalues) {
        sf::Vector2f itemPos = getItemPosition(item);
        sf::Vector2f itemSize = getItemSize(item);

        if (mousePos.x >= itemPos.x && mousePos.x <= itemPos.x + itemSize.x &&
            mousePos.y >= itemPos.y && mousePos.y <= itemPos.y + itemSize.y) {

            if (!firstItemSelected) {
                firstItem = item;
                firstItemSelected = true;
                enlargeItem(firstItem, true); // Powiększ wybrany element
            } else {
                secondItem = item;
                enlargeItem(firstItem, false); // Zmniejsz pierwszy wybrany element
                swapItems();
                swapCharValues(firstItem, secondItem);
                firstItemSelected = false;
            }
            break;
        }
    }
}


void Openall::swapItems() {
    setPosition(firstItem, secondItemPosition);
    setPosition(secondItem, firstItemPosition);
}

sf::Vector2f Openall::getItemPosition(char item) {

    switch (item) {
        case 'P': return sprite1.getPosition();
        case 'M': return sprite2.getPosition();
        case 'T': return sprite3.getPosition();
        case 'C': return carrottoline.getPosition();
        case 'S': return strawberrytoline.getPosition();
        case 'J': return sprite4.getPosition();
        case 'G': return sprite5.getPosition();
        case 'Z': return sprite6.getPosition();
        case 'A': return sprite7.getPosition();
        case 'E': return sprite8.getPosition();
        case 'F': return sprite9.getPosition();
        case 'I': return sprite10.getPosition();
        case 'R': return sprite11.getPosition();
        case 'L': return sprite12.getPosition();
        case 'D': return sprite13.getPosition();
        case 'W': return sprite14.getPosition();
        case 'K': return sprite15.getPosition();
        case 'U': return sprite16.getPosition();

        default: return sf::Vector2f(0.f, 0.f);
    }
}

void Openall::setPosition(char item, const sf::Vector2f& pos) {

    switch (item) {
        case 'P': sprite1.setPosition(pos); break;
        case 'M': sprite2.setPosition(pos); break;
        case 'T': sprite3.setPosition(pos); break;
        case 'C': carrottoline.setPosition(pos);break;
        case 'S': strawberrytoline.setPosition(pos);break;
        case 'J': sprite4.setPosition(pos);break;
        case 'G': sprite5.setPosition(pos);break;
        case 'Z': sprite6.setPosition(pos);break;
        case 'A': sprite7.setPosition(pos);break;
        case 'E': sprite8.setPosition(pos);break;
        case 'F': sprite9.setPosition(pos);break;
        case 'I': sprite10.setPosition(pos);break;
        case 'R': sprite11.setPosition(pos);break;
        case 'L': sprite12.setPosition(pos);break;
        case 'D': sprite13.setPosition(pos);break;
        case 'W': sprite14.setPosition(pos);break;
        case 'K': sprite15.setPosition(pos);break;
        case 'U': sprite16.setPosition(pos);break;
    }
}

sf::Vector2f Openall::getItemSize(char item) {

    switch (item) {
        case 'P': return sf::Vector2f(sprite1.getGlobalBounds().width, sprite1.getGlobalBounds().height);
        case 'M': return sf::Vector2f(sprite2.getGlobalBounds().width, sprite2.getGlobalBounds().height);
        case 'T': return sf::Vector2f(sprite3.getGlobalBounds().width, sprite3.getGlobalBounds().height);
        case 'C': return sf::Vector2f(carrottoline.getGlobalBounds().width, carrottoline.getGlobalBounds().height);
        case 'S': return sf::Vector2f(strawberrytoline.getGlobalBounds().width, strawberrytoline.getGlobalBounds().height);
        case 'J': return sf::Vector2f(sprite4.getGlobalBounds().width, sprite4.getGlobalBounds().height);
        case 'G': return sf::Vector2f(sprite5.getGlobalBounds().width, sprite5.getGlobalBounds().height);
        case 'Z': return sf::Vector2f(sprite6.getGlobalBounds().width, sprite6.getGlobalBounds().height);
        case 'A': return sf::Vector2f(sprite7.getGlobalBounds().width, sprite7.getGlobalBounds().height);
        case 'E': return sf::Vector2f(sprite8.getGlobalBounds().width, sprite8.getGlobalBounds().height);
        case 'F': return sf::Vector2f(sprite9.getGlobalBounds().width, sprite9.getGlobalBounds().height);
        case 'I': return sf::Vector2f(sprite10.getGlobalBounds().width, sprite10.getGlobalBounds().height);
        case 'R': return sf::Vector2f(sprite11.getGlobalBounds().width, sprite11.getGlobalBounds().height);
        case 'L': return sf::Vector2f(sprite12.getGlobalBounds().width, sprite12.getGlobalBounds().height);
        case 'D': return sf::Vector2f(sprite13.getGlobalBounds().width, sprite13.getGlobalBounds().height);
        case 'W': return sf::Vector2f(sprite14.getGlobalBounds().width, sprite14.getGlobalBounds().height);
        case 'K': return sf::Vector2f(sprite15.getGlobalBounds().width, sprite15.getGlobalBounds().height);
        case 'U': return sf::Vector2f(sprite16.getGlobalBounds().width, sprite16.getGlobalBounds().height);
        

        default: return sf::Vector2f(0.f, 0.f);
    }
}

void Openall::enlargeItem(char item, bool enlarge) {
    float scale = enlarge ? 1.2f : 1.0f; 
    switch (item) {
        case 'P': sprite1.setScale(1.2f, 1.2f); break;  
        case 'M': sprite2.setScale(1.2f, 1.2f); break;
        case 'T': sprite3.setScale(1.2f, 1.2f); break;  
        case 'C': carrottoline.setScale(1.2f, 1.2f); break;
        case 'S': strawberrytoline.setScale(1.2f, 1.2f); break; 
        case 'J': sprite4.setScale(1.2f, 1.2f); break;
        case 'G': sprite5.setScale(1.2f, 1.2f); break;  
        case 'Z': sprite6.setScale(1.2f, 1.2f); break;
        case 'A': sprite7.setScale(1.2f, 1.2f); break;  
        case 'E': sprite8.setScale(1.2f, 1.2f); break;
        case 'F': sprite9.setScale(1.2f, 1.2f); break;  
        case 'I': sprite10.setScale(1.2f, 1.2f); break;
        case 'R': sprite11.setScale(1.2f, 1.2f); break;  
        case 'L': sprite12.setScale(1.2f, 1.2f); break;
        case 'D': sprite13.setScale(1.2f, 1.2f); break; 
        case 'W': sprite14.setScale(1.2f, 1.2f); break;
        case 'K': sprite15.setScale(1.2f, 1.2f); break;
        case 'U': sprite16.setScale(1.2f, 1.2f); break;
default: break;

    }
}

void Openall::swapCharValues(char first, char second) {
    auto firstIt = std::find(charvalues.begin(), charvalues.end(), first);
    auto secondIt = std::find(charvalues.begin(), charvalues.end(), second);

    if (firstIt != charvalues.end() && secondIt != charvalues.end()) {
        std::iter_swap(firstIt, secondIt);


        int firstIndex = std::distance(charvalues.begin(), firstIt);
        int secondIndex = std::distance(charvalues.begin(), secondIt);


        if (firstIndex < intvalues.size() && secondIndex < intvalues.size()) {
            std::swap(intvalues[firstIndex], intvalues[secondIndex]);
        }
    }
}

std::vector<char> Openall::getCharValues() const {
    return charvalues;
}

std::vector<int> Openall::getIntValues() const {
    return intvalues;
}















