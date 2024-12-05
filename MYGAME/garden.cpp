
#include "garden.h"

Garden::Garden(sf::RenderWindow &window) : window(window),
                                           zlotowkiFile("zlotowki_value.txt"),
                                           isRunning(true),
                                           exit(window, sf::Vector2f(50, 50), sf::Vector2f(100, 100)),
                                           isSadzonkaPressed(false), currentImage(0), openall(nullptr)
                                           
{
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("aazdj/ogrodgrafikapopr.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    background.setTexture(backgroundTexture);

    if (!tankphoto.loadFromFile("aazdj/magazynn.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!psze1.loadFromFile("aazdj/sadzonka1.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!tru1.loadFromFile("aazdj/truskawka1.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    if (!mar1.loadFromFile("aazdj/marchewka1.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    if (!exittextur.loadFromFile("aazdj/wyjscie.png"))
    {
        std::cout << "blad\n";
    }
    exit.setTexture(exittextur);

    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);

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

void Garden::kopcephoto()
{

    if (!pasek.loadFromFile("aazdj/pasek.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    if (!kopiec.loadFromFile("aazdj/ziemia.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }

    pasek2.setTexture(pasek);
    pasek2.setPosition(260.0f, 680.0f);
    pasek2.setScale(0.9f, 0.9f);

    dokopiec.setTexture(kopiec);
    dokopiec2.setTexture(kopiec);
    dokopiec3.setTexture(kopiec);
    dokopiec4.setTexture(kopiec);

    dokopiec.setPosition(87.0f, 558.0f);
    dokopiec2.setPosition(365.0f, 558.0f);
    dokopiec3.setPosition(644.0f, 558.0f);
    dokopiec4.setPosition(922.0f, 558.0f);
}

void Garden::loadPositions()
{
    std::ifstream positionsFile("ogrod/positions.txt");
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
void Garden::addhelp()
{
    if (!zapytaniezdj.loadFromFile("znakzapytania/zapytanie2.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    znakzapytania.setTexture(zapytaniezdj);
    znakzapytania.setPosition(1080.0f, 660.0f);
    znakzapytania.setScale(0.2f, 0.2f);
}
void Garden::znakpomocy()
{
    if (!tablicapomoczdj.loadFromFile("znakzapytania/ogrodtablica.png"))
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

void Garden::loadTimes()
{
    std::ifstream timeFile("ogrod/czaszamkniecieogrod.txt");
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

void Garden::changeImage()
{

    for (size_t i = 0; i < planting.size(); ++i)
    {
        bool foundExisting = false;

        DisplayedImage newImage;

        if (planting[i] == 'P' && i >= displayedImages.size())
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
            newImage.sprite.setPosition(newImage.positionX, 520.0f);
            currentX += imageSpacing;
            newImage.sprite.setScale(0.15f, 0.15f);
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

        else if (planting[i] == 'M' && i >= displayedImages.size())
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
            newImage.sprite.setPosition(newImage.positionX + 13.0f, 528.0f);
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

        else if (planting[i] == 'T' && i >= displayedImages.size())
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
            newImage.sprite.setPosition(newImage.positionX - 2.0f, 486.0f);
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

        if (planting[i] == 'P' && timess.size() > 0)
        {
            if (displayedImages[i].timer.asSeconds() >= 10 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze2.loadFromFile("aazdj/pszenica3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze2);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 20.0f, 430.0f);

                displayedImages[i].sprite.setScale(0.35f, 0.35f);
                displayedImages[i].isThirdImageDisplayed = true;
            }
            else if (displayedImages[i].timer.asSeconds() >= 5 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze3.loadFromFile("aazdj/pszenica2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 20.0f, 453.0f);

                displayedImages[i].sprite.setScale(0.35f, 0.35f);
            }
        }

        else if (planting[i] == 'P')
        {
            if (displayedImages[i].timer.asSeconds() >= 10 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze2.loadFromFile("aazdj/pszenica3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze2);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX + 20.0f, 430.0f);

                displayedImages[i].sprite.setScale(0.35f, 0.35f);
                displayedImages[i].isThirdImageDisplayed = true;
            }
            else if (displayedImages[i].timer.asSeconds() >= 5 && !displayedImages[i].isThirdImageDisplayed)
            {
                if (!psze3.loadFromFile("aazdj/pszenica2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(psze3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 20.0f, 453.0f);

                displayedImages[i].sprite.setScale(0.35f, 0.35f);
            }
        }
        else if (planting[i] == 'M')
        {
            if (displayedImages[i].timer.asSeconds() >= 20 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!mar3.loadFromFile("aazdj/marchewka3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(mar3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 15.0f, 452.0f);
                displayedImages[i].sprite.setScale(0.6f, 0.6f);
                displayedImages[i].isThirdImageDisplayed = true;
            }

            else if (displayedImages[i].timer.asSeconds() >= 10 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!mar2.loadFromFile("aazdj/marchewka2.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(mar2);

                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 15.0f, 490.0f);
                displayedImages[i].sprite.setScale(0.9f, 0.9f);
            }
        }
        else if (planting[i] == 'T')
        {

            if (displayedImages[i].timer.asSeconds() >= 40 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!tru3.loadFromFile("aazdj/truskawka3.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(tru3);
                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 22.0f, 494.0f);
                displayedImages[i].sprite.setScale(0.5f, 0.5f);
                displayedImages[i].isThirdImageDisplayed = true;
            }

            else if (displayedImages[i].timer.asSeconds() >= 20 && !displayedImages[i].isThirdImageDisplayed)
            {

                if (!tru2.loadFromFile("aazdj/unnamed.png"))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                displayedImages[i].sprite.setTexture(tru2);

                displayedImages[i].sprite.setPosition(displayedImages[i].positionX - 20.0f, 480.0f);
                displayedImages[i].sprite.setScale(0.5f, 0.5f);
            }
        }
        addedtime = clocksadzonki[i].restart();
        displayedImages[i].timer += addedtime;
        window.draw(displayedImages[i].sprite);
    }
}

void Garden::addstorage()
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

void Garden::loadPlantingInfo()
{
    std::ifstream plantingFile("ogrod/planting_info.txt");

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

    std::ifstream plantingFiless("ogrod/pozycjedodatkowe.txt");
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
    std::ifstream timesFile("ogrod/times.txt");
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

void Garden::renderTopasek()
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
void Garden::addToPasek()
{
    position = 270;
    int interval = 150;
    int displayedVal = 0;
    int displayedValues = 0;
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
                displayedValues++;
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
                displayedValues++;
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
                displayedValues++;
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

void Garden::run()
{

    renderTopasek();

    openall = new Openall(window, ReadSigns, Readvalues);
    if(!ReadSigns.empty()){
    hoverDisplay = new HoverDisplays(window,ReadSigns[0],270,400,690,790);
    hoverDisplay2 = new HoverDisplays(window,ReadSigns[1],410,530,690,790);
    hoverDisplay3 = new HoverDisplays(window,ReadSigns[2],540,670,690,790);
    hoverDisplay4 = new HoverDisplays(window,ReadSigns[3],670,800,690,790);
    }
    loadPlantingInfo();
    loadPositions();
    loadTimes();

    while (window.isOpen())
    {

        handleEvents();
        // handleSadzonkaInteraction();
        // changeImage();

        czas = time(nullptr);
        czas_info = localtime(&czas);
        render();
        kopcephoto();
        // bleeaddtoline();
        sf::sleep(sf::milliseconds(10));
    }
}
void Garden::handleMouseClick(sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

        std::cout << "Mouse clicked at: X = " << worldPos.x << ", Y = " << worldPos.y << std::endl;
    }
}
void Garden::handleEvents()
{
    sf::Event event;
    if (event.type == sf::Event::Closed)
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

            if (openwerehouse)
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

            if (sorrywiondowisopen)
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
                else if (added < 4)
                {
                    if (sprite1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonepszenica)
                    {
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
                                    zasadzonepszenica = false;
                                    Readvalues.erase(Readvalues.begin() + i);
                                    ReadSigns.erase(ReadSigns.begin() + i);
                                }
                            }
                        }

                        planting.push_back('P');
                        isSadzonkaPressed = true;
                        added++;
                    }

                    else if (sprite2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonemarchew)
                    {
                        for (int i = 0; i < ReadSigns.size(); i++)
                        {
                            if (ReadSigns[i] == 'M')
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
                        planting.push_back('M');
                        isSadzonkaPressed = true;
                        added++;
                    }
                    else if (sprite3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && zasadzonetruskawka)
                    {
                        for (int i = 0; i < ReadSigns.size(); i++)
                        {
                            if (ReadSigns[i] == 'T')
                            {
                                if (Readvalues[i] > 1)
                                {
                                    Readvalues[i] -= 1;
                                }
                                else
                                {
                                    // PrintLine[i] = false;
                                    zasadzonetruskawka = false;
                                    Readvalues.erase(Readvalues.begin() + i);
                                    ReadSigns.erase(ReadSigns.begin() + i);
                                }
                            }
                        }
                        planting.push_back('T');
                        isSadzonkaPressed = true;
                        added++;
                    }
                }
                for (size_t i = 0; i < displayedImages.size(); ++i)
                {
                    if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'P' && displayedImages[i].timer.asSeconds() >= 10)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'P'; 
                        int wartosc;
                        bool znaleziono = false;
                        for (int j = 0; j < ReadSigns.size(); j++)
                        {
                            if (ReadSigns[j] == znak)
                            {

                                Readvalues[j] += 2;
                                znaleziono = true;

                                break;
                            }
                        }
                        if (!znaleziono)
                        {

                            ReadSigns.push_back('P');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'P')
                                {
                                    Readvalues[j] += 2;
                                    break;
                                }
                            }
                            zasadzonepszenica = true;
                        }
                        break;
                    }

                    else if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'M' && displayedImages[i].timer.asSeconds() >= 20)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'C';
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

                            ReadSigns.push_back('C');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'C')
                                {
                                    Readvalues[j] += 1;
                                    break;
                                }
                            }
                        }
                    }

                    else if (displayedImages[i].sprite.getGlobalBounds().contains(mousePos) && planting[i] == 'T' && displayedImages[i].timer.asSeconds() >= 40)
                    {
                        float positionX = displayedImages[i].positionX;

                        positions.push_back(positionX);
                        std::sort(positions.begin(), positions.end());

                        displayedImages.erase(displayedImages.begin() + i);
                        planting.erase(planting.begin() + i);
                        clocksadzonki.erase(clocksadzonki.begin() + i);
                        clicked = true;
                        added--;
                        char znak = 'S';
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

                            ReadSigns.push_back('S');
                            Readvalues.push_back(0);
                            for (int j = 0; j < ReadSigns.size(); j++)
                            {
                                if (ReadSigns[j] == 'S')
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

void Garden::savetimeall()
{

    // std::time_t currentTime = std::time(nullptr);

    std::ofstream timeFile("ogrod/czaszamkniecieogrod.txt");
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

void Garden::savePositions()
{
    std::ofstream positionsFile("ogrod/positions.txt");
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

void Garden::saveTimes()
{
    std::ofstream timesFile("ogrod/times.txt");
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

void Garden::savePlantingInfo()
{
    std::ofstream plantingFile("ogrod/planting_info.txt");
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

void Garden::savepositionAdditional()
{
    std::ofstream File("ogrod/pozycjedodatkowe.txt");
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

void Garden::render()
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
    window.draw(dokopiec4);
    window.draw(points);
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

void Garden::switchplace()
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
void Garden::switchTofarm()
{
    savePositions();
    saveTimes();
    savePlantingInfo();
    savetimeall();
    savepositionAdditional();
    switchplace();
    // std::cout<<displayedValues<<std::endl;
    Game game(window);
    game.run();
}

Garden::~Garden()
{
    delete openall;
    delete hoverDisplay;
    delete hoverDisplay2;
    delete hoverDisplay3;
    delete hoverDisplay4;
}
