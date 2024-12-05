
#include "orchard.h"

Orchard::Orchard(sf::RenderWindow &window) : window(window),
                                             zlotowkiFile("zlotowki_value.txt"),
                                             isRunning(true),
                                             exit(window, sf::Vector2f(50, 50), sf::Vector2f(100, 100)),
                                             isSadzonkaPressed(false), currentImage(0), currentX(-25.0f), openall(nullptr)
{
    window.setFramerateLimit(60);
//rysuje tło
    if (!backgroundTexture.loadFromFile("zdjeciasad/zdjeciesadu.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    background.setTexture(backgroundTexture);
//magazyn zjęcie 
    if (!tankphoto.loadFromFile("aazdj/magazynn.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!psze1.loadFromFile("zdjeciasad/jablko11.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!tru1.loadFromFile("zdjeciasad/sliwka11.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!mar1.loadFromFile("zdjeciasad/gruszka11.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    if (!exittextur.loadFromFile("aazdj/wyjscie.png"))
    {
        std::cout << "blad\n";
    }
    exit.setTexture(exittextur);
//skrzynka w rogu
    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);
//czcionka i pieniądze w rogu
    if (!font.loadFromFile("Flottflott.ttf"))
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
}
//dodaje kopce i pasek na dole
void Orchard::kopcephoto()
{

    if (!pasek.loadFromFile("aazdj/pasek.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    if (!kopiec.loadFromFile("zdjeciasad/ziemiasad.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    pasek2.setTexture(pasek);
    pasek2.setPosition(260.0f, 680.0f);
    pasek2.setScale(0.9f, 0.9f);

    dokopiec.setTexture(kopiec);
    dokopiec2.setTexture(kopiec);
    dokopiec3.setTexture(kopiec);
    dokopiec.setScale(0.4f, 0.4f);
    dokopiec2.setScale(0.4f, 0.4f);
    dokopiec3.setScale(0.4f, 0.4f);

    dokopiec.setPosition(187.0f, 575.0f);
    dokopiec2.setPosition(465.0f, 575.0f);
    dokopiec3.setPosition(752.0f, 575.0f);
}
//wyczytuje pozycje obecnych drzew ktore są w ziemi
void Orchard::loadPositions()
{
    std::ifstream positionsFile("zdjeciasad/pozycjadrzewa.txt");
    if (positionsFile.is_open())
    {
        int position;
        while (positionsFile >> position)
        {
            positionss.push_back(position);
        }
        positionsFile.close();
    }
    else
    {
        std::cerr << "Unable to open positions file!" << std::endl;
    }
}
//na podstawie daty oblicza sekundy które mineły 
void Orchard::loadTimes()
{
    std::ifstream timeFile("zdjeciasad/czascalydrzewa.txt");
    if (timeFile.is_open())
    {
        std::string line;
        if (std::getline(timeFile, line))
        {
            std::tm timeInfo = {};

            // Parsowanie daty i czasu ze wzorcem przy użyciu sscanf
            char day[4], month[4];
            int dayNum, hour, min, sec, year;

            if (std::sscanf(line.c_str(), "%3s %3s %d %d:%d:%d %d",
                            day, month, &dayNum, &hour, &min, &sec, &year) == 7)
            {

                // Konwersja nazw miesięcy i dni tygodnia na liczby
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
//duża funkcja ktora po pierwsze dodaje wartości do struktury po dodaniu wartości 
//do planting która zapisuje zasadzone nasiona a po drugie zmienia zdjęcia wraz z upływem czasu 
void Orchard::changeImage()
{

    for (size_t i = 0; i < planting.size(); ++i)
    {
        bool foundExisting = false;

        DisplayedImage newImage;

        if (planting[i] == 'J' && i >= displayedImages.size())
        {

            newImage.sprite.setTexture(psze1);

            if (positionss.size() > 0)
            {
                newImage.positionX = positionss[0];
                positionss.erase(positionss.begin());
            }
            else if (positions.size() > 0)
            {
                newImage.positionX = positions[0];
                positions.erase(positions.begin());
            }
            else
            {

                newImage.positionX = currentX;
            }

            newClock.restart(); // Resetowanie czasu dla nowego zegara
            clocksadzonki.push_back(newClock);
            clocksadzonki[i].restart();
            newImage.sprite.setPosition(newImage.positionX + 280.0f, 480.0f);
            currentX += imageSpacing;
            newImage.sprite.setScale(0.2f, 0.2f);
            if (timess.size() > 0)
            {

                newImage.timer = sf::seconds(timess[0]) + sf::seconds(differenceInSeconds);
                timess.erase(timess.begin());
            }
            else
            {
                newImage.timer = sf::Time::Zero;
            }
            displayedImages.push_back(newImage);
        }

        else if (planting[i] == 'G' && i >= displayedImages.size())
        {
            newImage.sprite.setTexture(mar1);
            if (positionss.size() > 0)
            {
                newImage.positionX = positionss[0];
                positionss.erase(positionss.begin());
            }
            else if (positions.size() > 0)
            {
                newImage.positionX = positions[0];
                positions.erase(positions.begin());
            }
            else
            {
                newImage.positionX = currentX;
            }
            newImage.sprite.setPosition(newImage.positionX + 300.0f, 490.0f);
            currentX += imageSpacing;
            newImage.sprite.setScale(0.2f, 0.2f);

            newClock.restart();
            clocksadzonki.push_back(newClock);
            clocksadzonki[i].restart();
            if (timess.size() > 0)
            {

                newImage.timer = sf::seconds(timess[0]) + sf::seconds(differenceInSeconds);
                timess.erase(timess.begin());
            }
            else
            {
                newImage.timer = sf::Time::Zero;
            }

            displayedImages.push_back(newImage);
        }

        else if (planting[i] == 'Z' && i >= displayedImages.size())
        {
            newImage.sprite.setTexture(tru1);
            if (positionss.size() > 0)
            {
                newImage.positionX = positionss[0];
                positionss.erase(positionss.begin());
            }
            else if (positions.size() > 0)
            {
                newImage.positionX = positions[0];
                positions.erase(positions.begin());
            }
            else
            {
                newImage.positionX = currentX;
            }
            newImage.sprite.setPosition(newImage.positionX + 290.0f, 456.0f);
            currentX += imageSpacing;
            newImage.sprite.setScale(0.2f, 0.2f);

            newClock.restart(); // Resetowanie czasu dla nowego zegara
            clocksadzonki.push_back(newClock);
            clocksadzonki[i].restart();
            if (timess.size() > 0)
            {

                newImage.timer = sf::seconds(timess[0]) + sf::seconds(differenceInSeconds);
                timess.erase(timess.begin());
            }
            else
            {
                newImage.timer = sf::Time::Zero;
            }

            displayedImages.push_back(newImage);
        }

        if (planting[i] == 'J')
        {
            if (displayedImages[i].timer.asSeconds() >= 10 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze2.loadFromFile("zdjeciasad/jablko3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze2);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 195.0f, 190.0f);

                displayedImages[i].sprite.setScale(0.6f, 0.6f);
                displayedImages[i].isThirdImageDisplayed = true;
            }
            else if (displayedImages[i].timer.asSeconds() >= 5 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze3.loadFromFile("zdjeciasad/jablko2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 210.0f, 243.0f);

                displayedImages[i].sprite.setScale(0.7f, 0.7f);
            }
        }
        else if (planting[i] == 'G')
        {
            if (displayedImages[i].timer.asSeconds() >= 20 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!mar3.loadFromFile("zdjeciasad/gruszka3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(mar3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 195.0f, 212.0f);
                displayedImages[i].sprite.setScale(0.6f, 0.6f);
                displayedImages[i].isThirdImageDisplayed = true;
            }

            else if (displayedImages[i].timer.asSeconds() >= 10 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!mar2.loadFromFile("zdjeciasad/gruszka2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(mar2);

                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 210.0f, 230.0f);
                displayedImages[i].sprite.setScale(0.7f, 0.7f);
            }
        }
        else if (planting[i] == 'Z')
        {

            if (displayedImages[i].timer.asSeconds() >= 40 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!tru3.loadFromFile("zdjeciasad/sliwka3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(tru3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 220.0f, 234.0f);
                displayedImages[i].sprite.setScale(0.6f, 0.6f);
                displayedImages[i].isThirdImageDisplayed = true;
            }

            else if (displayedImages[i].timer.asSeconds() >= 20 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!tru2.loadFromFile("zdjeciasad/sliwka2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(tru2);

                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 223.0f, 290.0f);
                displayedImages[i].sprite.setScale(0.6f, 0.6f);
            }
        }
        addedtime = clocksadzonki[i].restart();
        displayedImages[i].timer += addedtime;
        window.draw(displayedImages[i].sprite);
    }
}
//dodaje kropki na końcu paska
void Orchard::addstorage()
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
//wyczytuje wartości ktore są zasadzone do pliku
void Orchard::loadPlantingInfo()
{
    std::ifstream plantingFile("zdjeciasad/plantingdrzewa.txt");

    if (plantingFile.is_open())
    {
        char plant;

        while (plantingFile >> plant)
        {
            planting.push_back(plant);
            added++;
        }

        plantingFile.close();
    }
    else
    {
        std::cerr << "Unable to open planting info file!" << std::endl;
    }
//zapisuje poste pozycje na których nie ma zasadzonej rośliny
    std::ifstream plantingFiless("zdjeciasad/pozycjedodatkowedrzewa.txt");
    if (plantingFiless.is_open())
    {
        float plant;

        while (plantingFiless >> plant)
        {
            positions.push_back(plant);
        }

        plantingFiless.close();
    }
    else
    {
        std::cerr << "Unable to open planting info file!" << std::endl;
    }
    //zapisuje czas zasadzenia drzew
    std::ifstream timesFile("zdjeciasad/czasdrzewka.txt");
    if (timesFile.is_open())
    {
        float time;
        while (timesFile >> time)
        {
            timess.push_back(time);
        }
        timesFile.close();
    }
    else
    {
        std::cerr << "Unable to open times file!" << std::endl;
    }
}
//wyczytuje wartości z pliku które potem zapisywane sa na dole paska 
void Orchard::renderTopasek()
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
    // ReadSigns << "" << std::endl;
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
    // Readvalues << "" << std::endl;
    files.close();
}
//Generuje wartości na dole paska 
void Orchard::addToPasek()
{
    position = 270;
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

                sprite1.setTexture(obraz1);
                // sf::Sprite sprite1(obraz1);
                sprite1.setPosition(position, 700);
                sprite1.setScale(0.15f, 0.15f);
                if (zasadzonepszenica)
                {
                    window.draw(sprite1);
                    displayedValues++;
                }
            }
        }
        else if (ReadSigns[i] == 'M')
        {

            if (obraz2.loadFromFile("aazdj/nasionamarchewka.png"))
            {
                // sf::Sprite sprite2(obraz2);
                sprite2.setTexture(obraz2);
                sprite2.setPosition(position, 700);
                sprite2.setScale(0.7f, 0.7f);
                if (zasadzonemarchew)
                {
                    window.draw(sprite2);
                    displayedValues++;
                }
            }
        }
        else if (ReadSigns[i] == 'T')
        {

            if (obraz3.loadFromFile("aazdj/nasionatruskawka.png"))
            {
                // sf::Sprite sprite3(obraz3);
                sprite3.setTexture(obraz3);
                sprite3.setPosition(position + 10, 700);
                sprite3.setScale(0.7f, 0.7f);
                if (zasadzonetruskawka)
                {
                    window.draw(sprite3);
                    displayedValues++;
                }
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
        { // A

            if (obraz4.loadFromFile("zdjeciasad/nasionajablka.png"))
            {
                sprite4.setTexture(obraz4);
                sprite4.setPosition(position, 690);
                sprite4.setScale(0.4f, 0.4f);
                window.draw(sprite4);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'G')
        { // E

            if (obraz5.loadFromFile("zdjeciasad/nasionagruszki.png"))
            {
                sprite5.setTexture(obraz5);
                sprite5.setPosition(position, 690);
                sprite5.setScale(0.35f, 0.35f);
                window.draw(sprite5);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'Z')
        { // F

            if (obraz6.loadFromFile("zdjeciasad/nasionkosliwa.png"))
            {
                sprite6.setTexture(obraz6);
                sprite6.setPosition(position, 690);
                sprite6.setScale(0.4f, 0.4f);
                window.draw(sprite6);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'A')
        { // F

            if (obraz7.loadFromFile("zdjeciasad/jablkozdjecie.png"))
            {
                sprite7.setTexture(obraz7);
                sprite7.setPosition(position, 690);
                sprite7.setScale(0.2f, 0.2f);
                window.draw(sprite7);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'E')
        { // gruszka

            if (obraz8.loadFromFile("zdjeciasad/gruszkazdjecie.png"))
            {
                sprite8.setTexture(obraz8);
                sprite8.setPosition(position, 690);
                sprite8.setScale(0.2f, 0.2f);
                window.draw(sprite8);
                displayedValues++;
            }
        }
        else if (ReadSigns[i] == 'F')
        { // sliwka

            if (obraz9.loadFromFile("zdjeciasad/sliwkazdjecie.png"))
            {
                sprite9.setTexture(obraz9);
                sprite9.setPosition(position + 10, 690);
                sprite9.setScale(0.25f, 0.25f);
                window.draw(sprite9);
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
    //generuje ilość elementów
    xPos = 220;
    for (int i = 0; i < numIterations; ++i)
    {
        if (displayedVal >= 4)
        {
            break;
        }
        xPos += 140;
        if (Readvalues[i] != 0)
        {
            text.setString(std::to_string(Readvalues[i]));
            text.setPosition(xPos, 750);
            window.draw(text);
            displayedVal++;
        }
    }
}

void Orchard::run()
{

    renderTopasek();
    openall = new Openall(window, ReadSigns, Readvalues);
    //klasa która generuje zdjęcia po najechaniu na przedmiot
    if(!ReadSigns.empty()){
    hoverDisplay = new HoverDisplays(window,ReadSigns[0],270,400,690,790);
    hoverDisplay2 = new HoverDisplays(window,ReadSigns[1],410,530,690,790);
    hoverDisplay3 = new HoverDisplays(window,ReadSigns[2],540,670,690,790);
    hoverDisplay4 = new HoverDisplays(window,ReadSigns[3],670,800,690,790);
    }
    loadPlantingInfo();//po odworzeniu klasy wczytuje wartości
    loadPositions();
    loadTimes();

    while (window.isOpen())
    {

        handleEvents();

        czas = time(nullptr);
        czas_info = localtime(&czas);//wyczytuje obecny czas
        render();
        kopcephoto();
        sf::sleep(sf::milliseconds(10));
    }
}

void Orchard::handleEvents()
{
    sf::Event event;
    if (event.type == sf::Event::Closed)// po zamknięciu strony zapisuje wartości do pliku
    {
        savetimeall();
        savePositions();
        saveTimes();
        savePlantingInfo();
        savepositionAdditional();
        switchplace();
        window.close();
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            savePositions();
            saveTimes();
            savePlantingInfo();
            savetimeall();
            savepositionAdditional();
            switchplace();

            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (openwerehouse)//klasa generująca magazyn
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
            if (sorrywiondowisopen)//jeśli magazyn jest otwarty nie można niczego dookoła nacisnąć 
            {
                if (exit.isHoveredButton())
                {
                    switchTofarm();
                }
                else if (znakzapytania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    pomocotwarta = true;
                }
                else if (wyjscietablica.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    pomocotwarta = false;
                }
                //jeśli naciśniesz ja jakąś wartość gdzie masz możliwość zasadzenia to sadzi je obecnie
                // jeśli naciśniesz nasionko jabka 
                else if (added < 3)//limit 
                {
                    if (sprite4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonepszenica)
                    {
                        for (int i = 0; i < ReadSigns.size(); i++)
                        {
                            if (ReadSigns[i] == 'J')
                            {
                                if (Readvalues[i] > 1)
                                {
                                    Readvalues[i] -= 1;
                                }
                                else
                                {
                                    zasadzonepszenica = false;
                                    Readvalues.erase(Readvalues.begin() + i);
                                    ReadSigns.erase(ReadSigns.begin() + i);
                                }
                            }
                        }

                        planting.push_back('J');
                        isSadzonkaPressed = true;
                        added++;
                    }

                    else if (sprite5.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonemarchew)
                    {
                        for (int i = 0; i < ReadSigns.size(); i++)
                        {
                            if (ReadSigns[i] == 'G')
                            {
                                if (Readvalues[i] > 1)
                                {
                                    Readvalues[i] -= 1;
                                }
                                else
                                {
                                    zasadzonemarchew = false;
                                    Readvalues.erase(Readvalues.begin() + i);
                                    ReadSigns.erase(ReadSigns.begin() + i);
                                }
                            }
                        }
                        planting.push_back('G');
                        isSadzonkaPressed = true;
                        added++;
                    }
                    else if (sprite6.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonetruskawka)
                    {
                        for (int i = 0; i < ReadSigns.size(); i++)
                        {
                            if (ReadSigns[i] == 'Z')
                            {
                                if (Readvalues[i] > 1)
                                {
                                    Readvalues[i] -= 1;
                                }
                                else
                                {
                                    zasadzonetruskawka = false;
                                    Readvalues.erase(Readvalues.begin() + i);
                                    ReadSigns.erase(ReadSigns.begin() + i);
                                }
                            }
                        }
                        planting.push_back('Z');
                        isSadzonkaPressed = true;
                        added++;
                    }
                }
                //jeśli roślinki już urosną można je zebrać
                for (size_t i = 0; i < displayedImages.size(); ++i)
                {
                    if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'J' && displayedImages[i].timer.asSeconds() >= 10)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'A'; 
                        bool znaleziono = false;
                        for (int j = 0; j < ReadSigns.size(); j++)
                        {
                            if (ReadSigns[j] == znak)
                            {

                                Readvalues[j] += 1;
                                znaleziono = true;

                                break;
                            }
                        }
                        if (!znaleziono)
                        {

                            ReadSigns.push_back('A');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'A')
                                {
                                    Readvalues[j] += 1;
                                    break;
                                }
                            }
                        }
                    }

                    else if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'G' && displayedImages[i].timer.asSeconds() >= 20)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'E'; 
                        bool znaleziono = false;
                        for (int j = 0; j < ReadSigns.size(); j++)
                        {
                            if (ReadSigns[j] == znak)
                            {

                                Readvalues[j] += 1;
                                znaleziono = true;

                                break;
                            }
                        }
                        if (!znaleziono)
                        {

                            ReadSigns.push_back('E');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'E')
                                {
                                    Readvalues[j] += 1;
                                    break;
                                }
                            }
                        }
                    }

                    else if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'Z' && displayedImages[i].timer.asSeconds() >= 10)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'F';
                        bool znaleziono = false;
                        for (int j = 0; j < ReadSigns.size(); j++)
                        {
                            if (ReadSigns[j] == znak)
                            {

                                Readvalues[j] += 1;
                                znaleziono = true;

                                break;
                            }
                        }
                        if (!znaleziono)
                        {

                            ReadSigns.push_back('F');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'F')
                                {
                                    Readvalues[j] += 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (points.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                openwerehouse = !openwerehouse;
                sorrywiondowisopen = !sorrywiondowisopen;
            }
        }
    }
}
//zapisuje czas całkowity
void Orchard::savetimeall()
{

    // std::time_t currentTime = std::time(nullptr);

    std::ofstream timeFile("zdjeciasad/czascalydrzewa.txt");
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
//zapisuje ich pozycje
void Orchard::savePositions()
{
    std::ofstream positionsFile("zdjeciasad/pozycjadrzewa.txt");
    if (positionsFile.is_open())
    {
        for (DisplayedImage &pos : displayedImages)
        {
            positionsFile << pos.positionX << std::endl;
        }
        positionsFile << "" << std::endl;
        positionsFile.close();
    }
    else
    {
        std::cerr << "Unable to open positions file!" << std::endl;
    }
}
//zapisuje czas rośnięcia drzew
void Orchard::saveTimes()
{
    std::ofstream timesFile("zdjeciasad/czasdrzewka.txt");
    if (timesFile.is_open())
    {
        for (DisplayedImage &image : displayedImages)
        {
            timesFile << image.timer.asSeconds() << std::endl;
        }
        timesFile << "" << std::endl;
        timesFile.close();
    }
    else
    {
        std::cerr << "Unable to open times file!" << std::endl;
    }
}
//zapisuje która roślina jest obwecnie posadzona 
void Orchard::savePlantingInfo()
{
    std::ofstream plantingFile("zdjeciasad/plantingdrzewa.txt");
    if (plantingFile.is_open())
    {
        for (char plant : planting)
        {
            plantingFile << plant << std::endl;
        }
        plantingFile << "" << std::endl;
        plantingFile.close();
    }
    else
    {
        std::cerr << "Unable to open planting info file!" << std::endl;
    }
}
//zapisuje pozyje gdzie nie są zasadzone drzewa
void Orchard::savepositionAdditional()
{
    std::ofstream File("zdjeciasad/pozycjedodatkowedrzewa.txt");
    if (File.is_open())
    {
        for (float plant : positions)
        {
            File << plant << std::endl;
        }
        // File << "" << std::endl;
        File.close();
    }
    else
    {
        std::cerr << "Unable to open planting info file!" << std::endl;
    }
}
//dodaje pomoc
void Orchard::addhelp()
{
    if (!zapytaniezdj.loadFromFile("znakzapytania/zapytanie2.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    znakzapytania.setTexture(zapytaniezdj);
    znakzapytania.setPosition(1080.0f, 660.0f);
    znakzapytania.setScale(0.2f, 0.2f);
}
void Orchard::znakpomocy()
{
    if (!tablicapomoczdj.loadFromFile("znakzapytania/sadtablica.png"))
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
void Orchard::render()
{
    window.clear();

    window.draw(background);
    window.draw(pasek2);
    exit.handleMouseInteraction();
    exit.draw();
    window.draw(skrzynka);
    std::ifstream zlotowkiFile("zlotowki_value.txt");
    zlotowkiText.setString(std::to_string(zlotowkiValue));
    window.draw(zlotowkiText);

    changeImage();
    window.draw(dokopiec);
    window.draw(dokopiec2);
    window.draw(dokopiec3);

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
    addhelp();
    if (pomocotwarta)
    {
        znakpomocy();
    }
    window.draw(znakzapytania);
    if(!ReadSigns.empty()){
    hoverDisplay->update();
    hoverDisplay2->update();
    hoverDisplay3->update();
    hoverDisplay4->update();
    }
    window.display();
}

void Orchard::switchplace()
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
void Orchard::switchTofarm()
{
    savePositions();
    saveTimes();
    savePlantingInfo();
    savetimeall();
    savepositionAdditional();
    switchplace();
    Game game(window);
    game.run();
}

Orchard::~Orchard()
{
    delete openall;
    delete hoverDisplay;
    delete hoverDisplay2;
    delete hoverDisplay3;
    delete hoverDisplay4;
}