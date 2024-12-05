#include "hodowla.h"

Hodowla::Hodowla(sf::RenderWindow &window) : window(window),
                                             exit(window, sf::Vector2f(50, 50), sf::Vector2f(100, 100)),
                                             zlotowkiFile("zlotowki_value.txt"), speedMultiplier(0.01f),
                                             czasswinia(20.0f),
                                             czaskrowa(60.0f),
                                             czaskura(80.0f),
                                             timerBar(nullptr),
                                             timerBarkrowa(nullptr),
                                             timerBarkura(nullptr),
                                             openall(nullptr)
{

    if (!font.loadFromFile("Flottflott.ttf"))//czcionka
    {
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
    if (zlotowkiFile.is_open())
    {
        zlotowkiFile >> zlotowkiValue;
        zlotowkiFile.close();
    }

    if (!backgroundTexture.loadFromFile("hodowlazdj/hodowla1.png"))//tło
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    background.setTexture(backgroundTexture);
    if (!exittextur.loadFromFile("aazdj/wyjscie.png"))
    {
        std::cout << "blad\n";
    }
    exit.setTexture(exittextur);

    if (!pasek_zdj.loadFromFile("aazdj/pasek.png"))//pasek
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    pasek.setTexture(pasek_zdj);
    pasek.setPosition(260.0f, 680.0f);
    pasek.setScale(0.9f, 0.9f);
    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);

    if (!plotzdj.loadFromFile("hodowlazdj/plot.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    plot.setTexture(plotzdj);
    plot.setPosition(0.0f, 465.0f);
    plot.setScale(1.0f, 1.0f);
    size = sf::Vector2f(0.15f, 0.15f);
    targetSize = size;

    initialPositionKrowa = sf::Vector2f(370.f, 400.f);// dodaje początkowe pozycje zwierzętom
    initialPositionSwinia = sf::Vector2f(0.f, 420.f);
    initialPositionKura = sf::Vector2f(440.f, 700.f);
    if (!swiniaEndTexture.loadFromFile("hodowlazdj/swinka1zdechla.png"))//generuje obrazki pupili
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!krowaEndTexture.loadFromFile("hodowlazdj/krowa4zdechla.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!kuraEndTexture.loadFromFile("hodowlazdj/kura1zdechla.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    std::ifstream stateFile("hodowlazdj/animal_states.txt");//zapsuje czy zwierzątka żyją czy nie 
    if (stateFile.is_open())
    {
        stateFile >> swinkazyje >> krowkazyje >> kurkazyje;
        stateFile.close();
    }
    else
    {
        swinkazyje = false;
        krowkazyje = false;
        kurkazyje = false;
    }
}
//dodaje pomoc, znak zapytania w rogu
void Hodowla::addhelp()
{
    if (!zapytaniezdj.loadFromFile("znakzapytania/zapytanie2.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    znakzapytania.setTexture(zapytaniezdj);
    znakzapytania.setPosition(1080.0f, 660.0f);
    znakzapytania.setScale(0.2f, 0.2f);
}
//wyczytuje wartości żeby potem je dodać na pasku zadan na dole
void Hodowla::renderTopasek()
{
    std::ifstream file("wypisz_values.txt");
    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (file >> Signs)
    {
        if (Signs != ' ')
        {
            ReadSigns.push_back(Signs);
        }
    }
    file.close();

    std::ifstream files("letter_values.txt");
    if (!files.is_open())
    {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    while (files >> valuess)
    {
        if (valuess != ' ')
        {
            Readvalues.push_back(valuess);
        }
    }
    files.close();
}
//zdjęcia trzech kropek, które otwierają magazyn 
void Hodowla::addstorage()
{
    if (!pointsphoto.loadFromFile("aazdj/kropki.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    points.setTexture(pointsphoto);
    points.setPosition(830.0f, 725.0f);
    points.setScale(0.4f, 0.4f);
    window.draw(points);
}
//generowanie wartości do paska na dole
void Hodowla::addToPasek()
{
    int position = 270;
    int interval = 150;
    int displayedValues = 0;
    int displayedVal = 0;
    int numIterations = std::min(static_cast<int>(ReadSigns.size()), 4);
    for (int i = 0; i < numIterations; i++)
    {
        if (displayedValues >= 4)
        {
            break; 
        }
        if (ReadSigns[i] == 'P')
        {

            if (obraz1.loadFromFile("aazdj/nasiono1.png"))
            {
                ziarenko.setTexture(obraz1);
                ziarenko.setPosition(position, 700);
                // ziarenko.setScale(size);
                window.draw(ziarenko);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'M')
        {

            if (obraz2.loadFromFile("aazdj/nasionamarchewka.png"))
            {
                sf::Sprite sprite(obraz2);
                sprite.setPosition(position, 700);
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'T')
        {

            if (obraz3.loadFromFile("aazdj/nasionatruskawka.png"))
            {
                sf::Sprite sprite(obraz3);
                sprite.setPosition(position + 10, 700);
                sprite.setScale(0.7f, 0.7f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'C')
        {

            if (carrottolinephoto.loadFromFile("aazdj/carrot.png"))
            {
                // sf::Sprite sprite3(obraz3);
                carrottoline.setTexture(carrottolinephoto);
                carrottoline.setPosition(position - 5, 700);
                carrottoline.setScale(0.25f, 0.25f);
                window.draw(carrottoline);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'S')
        {

            if (strawberrytolinephoto.loadFromFile("aazdj/truskawka.png"))
            {
                // sf::Sprite sprite3(obraz3);
                strawberrytoline.setTexture(strawberrytolinephoto);
                strawberrytoline.setPosition(position - 10, 700);
                strawberrytoline.setScale(0.3f, 0.3f);
                window.draw(strawberrytoline);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'J')
        {

            if (obraz4.loadFromFile("zdjeciasad/nasionajablka.png"))
            {
                sf::Sprite sprite(obraz4);
                sprite.setPosition(position, 690);
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'G')
        {

            if (obraz5.loadFromFile("zdjeciasad/nasionagruszki.png"))
            {
                sf::Sprite sprite(obraz5);
                sprite.setPosition(position, 690);
                sprite.setScale(0.35f, 0.35f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'Z')
        {

            if (obraz6.loadFromFile("zdjeciasad/nasionkosliwa.png"))
            {
                sf::Sprite sprite(obraz6);
                sprite.setPosition(position, 690);
                sprite.setScale(0.4f, 0.4f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'A')
        { // F

            if (obraz7.loadFromFile("zdjeciasad/jablkozdjecie.png"))
            {
                sf::Sprite sprite(obraz7);
                sprite.setPosition(position, 690);
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'E')
        { // gruszka

            if (obraz8.loadFromFile("zdjeciasad/gruszkazdjecie.png"))
            {
                sf::Sprite sprite(obraz8);
                sprite.setPosition(position, 690);
                sprite.setScale(0.2f, 0.2f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'F')
        { // sliwka

            if (obraz9.loadFromFile("zdjeciasad/sliwkazdjecie.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position + 10, 690);
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'I')
        { // miedz

            if (obraz9.loadFromFile("kopalnia/sztabkamiedz.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 720);
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'R')
        { // srebro

            if (obraz9.loadFromFile("kopalnia/sztabkasrebro.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 720);
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'L')
        { // zloto

            if (obraz9.loadFromFile("kopalnia/sztabkazloto.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 720);
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'D')
        { // diament

            if (obraz9.loadFromFile("kopalnia/diament.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position - 10, 720);
                sprite.setScale(0.25f, 0.25f);
                window.draw(sprite);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'W')
        {

            if (obraz9.loadFromFile("hodowlazdj/jajkoswinka.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 690);
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        else if (ReadSigns[i] == 'K')
        {

            if (obraz9.loadFromFile("hodowlazdj/jajkokrowka.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 690);
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        else if (ReadSigns[i] == 'U')
        {

            if (obraz9.loadFromFile("hodowlazdj/jajkokura.png"))
            {
                sf::Sprite sprite(obraz9);
                sprite.setPosition(position, 690);
                sprite.setScale(0.3f, 0.3f);
                window.draw(sprite);
            }
        }
        position += interval;
    }
    xPos = 220;
    for (int i = 0; i < numIterations; ++i)
    {
        xPos += 140;
        if (Readvalues[i] != 0)
        {
            text.setString(std::to_string(Readvalues[i]));
            text.setPosition(xPos, 750);
            window.draw(text);
        }
    }
}
//zamienia czas na sekundy
void Hodowla::loadtimes()
{
    std::ifstream timeFile("hodowlazdj/czaszamknieciahodowla.txt");
    if (timeFile.is_open())
    {
        std::string line;
        if (std::getline(timeFile, line))
        {
            std::tm timeInfo = {};

            char day[4], month[4];
            int dayNum, hour, min, sec, year;

            if (std::sscanf(line.c_str(), "%3s %3s %d %d:%d:%d %d",
                            day, month, &dayNum, &hour, &min, &sec, &year) == 7)
            {

                const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
                const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

                for (int i = 0; i < 12; ++i)
                {
                    if (month == std::string(months[i]))
                    {
                        timeInfo.tm_mon = i;
                        break;
                    }
                }

                for (int i = 0; i < 7; ++i)
                {
                    if (day == std::string(days[i]))
                    {
                        timeInfo.tm_wday = i;
                        break;
                    }
                }

                timeInfo.tm_mday = dayNum;
                timeInfo.tm_hour = hour;
                timeInfo.tm_min = min;
                timeInfo.tm_sec = sec;
                timeInfo.tm_year = year - 1900;

                std::time_t timeValue = std::mktime(&timeInfo);
                std::chrono::system_clock::time_point savedTime = std::chrono::system_clock::from_time_t(timeValue);

                std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
                difference = currentTime - savedTime;
                differenceInSeconds = difference.count();
            }
            else
            {
                std::cerr << "Failed to parse time!" << std::endl;
            }
        }
        timeFile.close();
    }
    else
    {
        std::cerr << "Unable to open the file to read time!" << std::endl;
    }
}
//dodaje zwierzęta zdjęcie do wartości sprite
void Hodowla::dodajzwierzeta()
{
    if (!krowazdj.loadFromFile("hodowlazdj/krowa1.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    krowa.setTexture(krowazdj);
    // krowa.setPosition(0, 360);
    krowa.setScale(0.7f, 0.7f);
    if (!swiniazdj.loadFromFile("hodowlazdj/swinka2.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    swinia.setTexture(swiniazdj);
    // krowa.setPosition(0, 360);
    swinia.setScale(0.7f, 0.7f);
    if (!kurazdj.loadFromFile("hodowlazdj/kura2.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    kura.setTexture(kurazdj);
    // krowa.setPosition(0, 360);
    kura.setScale(0.7f, 0.7f);
}

void Hodowla::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)//gdy wychodzisz z klasy zapisuje wartości 
        {
            savetimeall();
            zyjeczynie();
            saveTimeToFile();
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (openwerehouse)//otwiera mazagyn
            {

                openall->handleMouseEvent(event);
                ReadSigns = openall->getCharValues();
                Readvalues = openall->getIntValues();
            }
        }
        
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
            if (exit.isHoveredButton())
            {
                switchTofarm();
            }
            else if (points.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                openwerehouse = !openwerehouse;
            }
            else if (znakzapytania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                pomocotwarta = true;
            }
            else if (wyjscietablica.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                pomocotwarta = false;
            }

            if (ziarenko.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))//gdy naciśniesz ziarenko pszenicy ono rośnie
            {
                if (!ziarenkoClicked)
                {
                    targetSize = ziarenko.getScale() + sf::Vector2f(0.1f, 0.1f);
                    ziarenkoClicked = true;
                }
                else
                {
                    targetSize = size;
                    ziarenkoClicked = false;
                }
            }
//odblokowywuje zwierzęta jeśli jest taka możliwość
            else if (klodkaswinia.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !swinkazyje)
            {
                if (std::find(ReadSigns.begin(), ReadSigns.end(), 'W') != ReadSigns.end())
                {
                    swinkazyje = true;
                    timerBar->reset();
                    for (int i = 0; i < ReadSigns.size(); i++)
                    {
                        if (ReadSigns[i] == 'W')
                        {
                            if (Readvalues[i] > 1)
                            {
                                Readvalues[i] -= 1;
                            }
                            else
                            {
                                Readvalues.erase(Readvalues.begin() + i);
                                ReadSigns.erase(ReadSigns.begin() + i);
                            }
                        }
                    }
                }
            }
            else if (klodkakrowa.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !krowkazyje)
            {
                if (std::find(ReadSigns.begin(), ReadSigns.end(), 'K') != ReadSigns.end())
                {
                    krowkazyje = true;
                    timerBarkrowa->reset();
                    for (int i = 0; i < ReadSigns.size(); i++)
                    {
                        if (ReadSigns[i] == 'K')
                        {
                            if (Readvalues[i] > 1)
                            {
                                Readvalues[i] -= 1;
                            }
                            else
                            {
                                Readvalues.erase(Readvalues.begin() + i);
                                ReadSigns.erase(ReadSigns.begin() + i);
                            }
                        }
                    }
                }
            }
            else if (klodkakura.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && !kurkazyje)
            {
                if (std::find(ReadSigns.begin(), ReadSigns.end(), 'U') != ReadSigns.end())
                {
                    kurkazyje = true;
                    timerBarkura->reset();
                    for (int i = 0; i < ReadSigns.size(); i++)
                    {
                        if (ReadSigns[i] == 'U')
                        {
                            if (Readvalues[i] > 1)
                            {
                                Readvalues[i] -= 1;
                            }
                            else
                            {
                                Readvalues.erase(Readvalues.begin() + i);
                                ReadSigns.erase(ReadSigns.begin() + i);
                            }
                        }
                    }
                }
            }
            if (swinia.getGlobalBounds().contains(mousePos) && timerBar->isTimeUp())//jeśli czas minie zwierzątko ginie
            {
                swinkazyje = false;
            }
            if (krowa.getGlobalBounds().contains(mousePos) && timerBarkrowa->isTimeUp())
            {
                krowkazyje = false;
            }
            if (kura.getGlobalBounds().contains(mousePos) && timerBarkura->isTimeUp())
            {
                kurkazyje = false;
            }
            else if (ziarenkoClicked && krowa.getGlobalBounds().contains(mousePos))//karmienie pszenicą zwierząt
            {

                timerBarkrowa->addTime(2.0f);
                for (int i = 0; i < ReadSigns.size(); i++)
                {
                    if (ReadSigns[i] == 'P')
                    {
                        if (Readvalues[i] > 1)
                        {
                            Readvalues[i] -= 1;
                        }
                        else
                        {
                            Readvalues.erase(Readvalues.begin() + i);
                            ReadSigns.erase(ReadSigns.begin() + i);
                        }
                    }
                }
            }
            else if (ziarenkoClicked && swinia.getGlobalBounds().contains(mousePos))
            {
                timerBar->addTime(2.0f);
                for (int i = 0; i < ReadSigns.size(); i++)
                {
                    if (ReadSigns[i] == 'P')
                    {
                        if (Readvalues[i] > 1)
                        {
                            Readvalues[i] -= 1;
                        }
                        else
                        {
                            Readvalues.erase(Readvalues.begin() + i);
                            ReadSigns.erase(ReadSigns.begin() + i);
                        }
                    }
                }
            }
            else if (ziarenkoClicked && kura.getGlobalBounds().contains(mousePos))
            {
                timerBarkura->addTime(2.0f);
                for (int i = 0; i < ReadSigns.size(); i++)
                {
                    if (ReadSigns[i] == 'P')
                    {
                        if (Readvalues[i] > 1)
                        {
                            Readvalues[i] -= 1;
                        }
                        else
                        {
                            Readvalues.erase(Readvalues.begin() + i);
                            ReadSigns.erase(ReadSigns.begin() + i);
                        }
                    }
                }
            }
        }
    }
}

void Hodowla::updateCowMovementKrowa()//generuje krowę, jej tor ruchu i pozostałych zwirząt
{
    if (isKrowaAlive && krowkazyje)
    {
        static sf::Clock movementClock;
        static sf::Clock stopClock;
        static bool isMoving = true;
        static bool isStopped = false;
        static float vx = 1;
        static float vy = 0;
        static float GRAVITY = 0.002;
        static const float moveTime = 3.f;
        static const float stopTime = 2.5f;

        if (isMoving)
        {

            sf::Vector2f velocity(vx, vy);
            krowa.move(velocity);

            if (movementClock.getElapsedTime().asSeconds() >= moveTime)
            {
                isMoving = false;
                isStopped = true;
                vx = -vx;
                movementClock.restart();
                stopClock.restart();
            }
        }
        else if (isStopped)
        {

            if (stopClock.getElapsedTime().asSeconds() >= stopTime)
            {
                isStopped = false;
                isMoving = true;
                movementClock.restart();
            }
        }

        if (vx < 0)
        {
            if (!krowazdj.loadFromFile("hodowlazdj/krowa4.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            krowa.setTexture(krowazdj);
        }
        else
        {
            if (!krowazdj.loadFromFile("hodowlazdj/krowa1.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            krowa.setTexture(krowazdj);
        }
    }
}

void Hodowla::updateCowMovementKura()
{
    if (isKuraAlive && kurkazyje)
    {
        static sf::Clock movementClockx;
        static sf::Clock stopClock;
        static bool isMoving = true;
        static bool isStopped = false;
        static float vx = 1;
        static float vy = 0;
        static float GRAVITY = 0.002;
        static const float moveTime = 3.f;
        static const float stopTime = 2.f;

        if (isMoving)
        {

            sf::Vector2f velocity(vx, vy);
            kura.move(velocity);

            if (movementClockx.getElapsedTime().asSeconds() >= moveTime)
            {
                isMoving = false;
                isStopped = true;
                vx = -vx;
                movementClockx.restart();
                stopClock.restart();
            }
        }
        else if (isStopped)
        {

            if (stopClock.getElapsedTime().asSeconds() >= stopTime)
            {
                isStopped = false;
                isMoving = true;
                movementClockx.restart();
            }
        }

        if (vx < 0)
        {
            if (!kurazdj.loadFromFile("hodowlazdj/kura1.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            kura.setTexture(kurazdj);
        }
        else
        {
            if (!kurazdj.loadFromFile("hodowlazdj/kura2.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            kura.setTexture(kurazdj);
        }
    }
}

void Hodowla::saveAnimalPositions()// zapisuje pozycje zwierząt po wyjściu z pliku 
{
    std::ofstream file("animal_positions.txt");
    if (file.is_open())
    {
        file << krowa.getPosition().x << " " << krowa.getPosition().y << std::endl;
        file << swinia.getPosition().x << " " << swinia.getPosition().y << std::endl;
        file << kura.getPosition().x << " " << kura.getPosition().y << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Nie można otworzyć pliku do zapisu pozycji zwierząt." << std::endl;
    }
}

void Hodowla::loadAnimalPositions()// generuje pozycje zwierząt po otwarciu plik, jeśli w pliku nie ma danej pozycji daje standardowe
{
    std::ifstream file("animal_positions.txt");
    float x, y;
    if (file.is_open())
    {
        if (file >> x >> y)
        {
            krowa.setPosition(x, y);
        }
        if (file >> x >> y)
        {
            swinia.setPosition(x, y);
        }
        if (file >> x >> y)
        {
            kura.setPosition(x, y);
        }
        file.close();
    }
    else
    {
        std::cerr << "Nie można otworzyć pliku do wczytania pozycji zwierząt." << std::endl;

        krowa.setPosition(initialPositionKrowa);
        swinia.setPosition(initialPositionSwinia);
        kura.setPosition(initialPositionKura);
    }
}

void Hodowla::updateCowMovementSwinia()
{
    if (isSwiniaAlive && swinkazyje)
    {
        static sf::Clock movementClocks;
        static sf::Clock stopClock;
        static float vx = 1;
        static float vy = 0;
        static float GRAVITY = 0.002;
        static bool isMoving = true;
        static bool isStopped = false;
        static const float moveTime = 3.f;
        static const float stopTime = 3.f;

        if (isMoving)
        {

            sf::Vector2f velocity(vx, vy);
            swinia.move(velocity);

            if (movementClocks.getElapsedTime().asSeconds() >= moveTime)
            {
                isMoving = false;
                isStopped = true;
                vx = -vx;
                movementClocks.restart();
                stopClock.restart();
            }
        }
        else if (isStopped)
        {

            if (stopClock.getElapsedTime().asSeconds() >= stopTime)
            {
                isStopped = false;
                isMoving = true;
                movementClocks.restart();
            }
        }

        if (vx < 0)
        {
            if (!swiniazdj.loadFromFile("hodowlazdj/swinka1.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            swinia.setTexture(swiniazdj);
        }
        else
        {
            if (!swiniazdj.loadFromFile("hodowlazdj/swinka2.png"))
            {
                std::cerr << "Błąd podczas wczytywania." << std::endl;
            }
            swinia.setTexture(swiniazdj);
        }
    }
}

void Hodowla::deadanimals()// jeśli czas się skończy zwierzątka umierają 
{
    if (timerBar->isTimeUp())
    {
        swinia.setTexture(swiniaEndTexture);
        isSwiniaAlive = false;
        swinia.setPosition(50.f, 500.f);
    }

    if (timerBarkrowa->isTimeUp())
    {
        krowa.setTexture(krowaEndTexture);
        isKrowaAlive = false;
        krowa.setPosition(460.f, 500.f);
    }

    if (timerBarkura->isTimeUp())
    {
        kura.setTexture(kuraEndTexture);
        isKuraAlive = false;
        kura.setPosition(890.f, 500.f);
    }
}
void Hodowla::run()
{
    loadTimeFromFile();
    //klasa generująca zielone paski na górze zwierząt
    timerBar = new TimerBar(czasswinia, (czasswinia / 20) * 200.0, 20.0f, sf::Color::Green);
    timerBarkrowa = new TimerBar(czaskrowa, (czaskrowa / 60) * 200.0, 20.0f, sf::Color::Green);
    timerBarkura = new TimerBar(czaskura, (czaskura / 80) * 200.0, 20.0f, sf::Color::Green);
    timerBar->setPosition(100.0f, 390.0f);
    timerBarkrowa->setPosition(500.0f, 390.0f);
    timerBarkura->setPosition(900.0f, 390.0f);
    loadAnimalPositions();
    renderTopasek();
    openall = new Openall(window, ReadSigns, Readvalues);
        if(!ReadSigns.empty()){
    hoverDisplay = new HoverDisplays(window,ReadSigns[0],270,400,690,790);//generuje dymki
    hoverDisplay2 = new HoverDisplays(window,ReadSigns[1],410,530,690,790);
    hoverDisplay3 = new HoverDisplays(window,ReadSigns[2],540,670,690,790);
    hoverDisplay4 = new HoverDisplays(window,ReadSigns[3],670,800,690,790);
    }
    while (window.isOpen())
    {
        czas = time(nullptr);
        czas_info = localtime(&czas);
        handleEvents();
        render();
    }
}
//zapisuje wartości z paska gdy wychodzisz z klasy
void Hodowla::switchplace()
{
    std::ofstream wypiszFile("wypisz_values.txt");
    if (wypiszFile.is_open())
    {
        for (char znak : ReadSigns)
        {
            wypiszFile << znak << " ";
        }
        wypiszFile.close();
    }
    std::ofstream letterFile("letter_values.txt");
    if (letterFile.is_open())
    {
        for (int value : Readvalues)
        {
            letterFile << value << " ";
        }
        letterFile.close();
    }
}
void Hodowla::znakpomocy()
{
    if (!tablicapomoczdj.loadFromFile("znakzapytania/hodowlatablica.png"))
    {
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
//generuje kłodkę gdy zwierzęta nie są jeszcze odblokowane 
void Hodowla::addpadlock()
{
    if (!zdjklodka.loadFromFile("hodowlazdj/klodka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!swinkazyje)
    {
        klodkaswinia.setTexture(zdjklodka);
        klodkaswinia.setPosition(100.0f, 400.0f);
        klodkaswinia.setScale(0.3f, 0.3f);
        window.draw(klodkaswinia);
    }
    if (!krowkazyje)
    {
        klodkakrowa.setTexture(zdjklodka);
        klodkakrowa.setPosition(500.0f, 400.0f);
        klodkakrowa.setScale(0.3f, 0.3f);
        window.draw(klodkakrowa);
    }
    if (!kurkazyje)
    {
        klodkakura.setTexture(zdjklodka);
        klodkakura.setPosition(900.0f, 400.0f);
        klodkakura.setScale(0.3f, 0.3f);
        window.draw(klodkakura);
    }
}

void Hodowla::render()
{
    window.clear();
    window.draw(background);
    exit.handleMouseInteraction();
    exit.draw();
    window.draw(pasek);
    window.draw(skrzynka);

    if (ziarenko.getScale() != targetSize)
    {
        ziarenko.setScale(targetSize);
    }
    dodajzwierzeta();
    std::ifstream zlotowkiFile("zlotowki_value.txt");
    zlotowkiText.setString(std::to_string(zlotowkiValue));
    window.draw(zlotowkiText);
    window.draw(plot);
    updateCowMovementKrowa();
    updateCowMovementSwinia();
    updateCowMovementKura();
    deadanimals();
    if (krowkazyje)
    {
        window.draw(krowa);
    }
    if (swinkazyje)
    {
        window.draw(swinia);
    }
    if (kurkazyje)
    {
        window.draw(kura);
    }
    addhelp();

    if (pomocotwarta)
    {
        znakpomocy();
    }
    window.draw(znakzapytania);
    addpadlock();

    // std::cout<<Readvalues[0]<<std::endl;
    if (swinkazyje)
    {
    timerBar->update();
    timerBar->draw(window);
    }
    if (krowkazyje)
    {
    timerBarkrowa->update();
    timerBarkrowa->draw(window);
    }
    if (kurkazyje)
    {
    timerBarkura->update();
    timerBarkura->draw(window);
    }
    addstorage();
    if (!openwerehouse)
    {
        addToPasek();
    }
    else
    {

        openall->drawtank();
        openall->addsToPasek();
    }
        if(!ReadSigns.empty()){
    hoverDisplay->update();
    hoverDisplay2->update();
    hoverDisplay3->update();
    hoverDisplay4->update();
    }
    window.display();
}

void Hodowla::savetimeall()
{

    // std::time_t currentTime = std::time(nullptr);

    std::ofstream timeFile("hodowlazdj/czaszamknieciahodowla.txt");
    if (timeFile.is_open())
    {

        timeFile << asctime(czas_info) << std::endl;
        timeFile.close();
    }
    else
    {
        std::cerr << "Unable to open the file to save time!" << std::endl;
    }
}
// zapsiuje 0,1 gdy zwierzę żyje czy nie
void Hodowla::zyjeczynie()
{
    std::ofstream stateFile("hodowlazdj/animal_states.txt");
    if (stateFile.is_open())
    {
        stateFile << swinkazyje << " " << krowkazyje << " " << kurkazyje << std::endl;
        stateFile.close();
    }
    else
    {
        std::cerr << "Unable to open the file to save states!" << std::endl;
    }
}
//generuje czs życia
void Hodowla::saveTimeToFile()
{
    std::ofstream file("hodowlazdj/czaszycia.txt");
    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku do zapisu czasu." << std::endl;
        return;
    }
    if (swinkazyje)
    {
        remainingTimeSwinia = timerBar->getRemainingTime();
    }
    else
    {
        remainingTimeSwinia = 20.0;
    }
    if (krowkazyje)
    {
        remainingTimeKrowa = timerBarkrowa->getRemainingTime();
    }
    else
    {
        remainingTimeKrowa = 60.0;
    }
    if (kurkazyje)
    {
        remainingTimeKura = timerBarkura->getRemainingTime();
    }
    else
    {
        remainingTimeKura = 80.0;
    }
    file << remainingTimeSwinia << " " << remainingTimeKrowa << " " << remainingTimeKura;
    file.close();
}
void Hodowla::loadTimeFromFile()
{
    std::ifstream file("hodowlazdj/czaszycia.txt");
    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku do odczytu czasu." << std::endl;
        czasswinia = 20.0f;
        czaskrowa = 60.0f;
        czaskura = 80.0f;
        return;
    }

    file >> czasswinia >> czaskrowa >> czaskura;
    file.close();
}
void Hodowla::switchTofarm()
{
    savetimeall();
    switchplace();
    saveTimeToFile();
    zyjeczynie();
    Game game(window);
    game.run();
}
Hodowla::~Hodowla()
{
    delete openall;
    delete timerBar;
    delete timerBarkrowa;
    delete timerBarkura;
    delete hoverDisplay;
    delete hoverDisplay2;
    delete hoverDisplay3;
    delete hoverDisplay4;
}