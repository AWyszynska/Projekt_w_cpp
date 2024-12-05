
#include "cave.h"

Cave::Cave(sf::RenderWindow &window) : window(window),
                                       exit(window, sf::Vector2f(50, 50), sf::Vector2f(100, 100)),
                                       zlotowkiFile("zlotowki_value.txt"), imagePaths({"kopalnia/skala1.png", "kopalnia/skala2.png", "kopalnia/skala3.png", "kopalnia/skala4.png", "kopalnia/skala5.png", "kopalnia/skala6.png"}),
                                       gen(rd()), dis(0, imagePaths.size() - 1), openall(nullptr)
{
    //Wczytuje czcionkę
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
    //Ustawia tło
    if (!backgroundTexture.loadFromFile("kopalnia/kopalnia.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    background.setTexture(backgroundTexture);
    //zdjęcie iksa
    if (!exittextur.loadFromFile("aazdj/wyjscie.png"))
    {
        std::cout << "blad\n";
    }
    exit.setTexture(exittextur);
    //Ustawia pasek na dole
    if (!pasek_zdj.loadFromFile("aazdj/pasek.png"))
    {
        std::cerr << "Błąd podczas wczytywania." << std::endl;
    }
    pasek.setTexture(pasek_zdj);
    pasek.setPosition(260.0f, 680.0f);
    pasek.setScale(0.9f, 0.9f);
    //ustawia skrzynkę
    if (!skrzynkazdj.loadFromFile("aazdj/skrzynka.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    skrzynka.setTexture(skrzynkazdj);
    skrzynka.setPosition(950.0f, 0.0f);
    skrzynka.setScale(0.5f, 0.5f);
}
//Wczytuje z pliku wartości żeby ustawic je potem na dole paska
void Cave::renderTopasek()
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
//dodaje te 3 kropeczki na dole
void Cave::addstorage()
{
    if (!pointsphoto.loadFromFile("aazdj/kropki.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    points.setTexture(pointsphoto);
    points.setPosition(830.0f, 725.0f);
    points.setScale(0.4f, 0.4f);
    window.draw(points);

    if (!skala1zdj.loadFromFile("kopalnia/skala1.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    // skala1.setTexture(skala1zdj);
    // skala1.setPosition(300.0f, 300.0f);
    // skala1.setScale(0.5f, 0.5f);
}
//Oblicza czas skaly wygenerowanej i sprawia że rośnie
void Cave::renderskala() {
    if (isRightMouseDown) {
        elapsedskala = clockskala.getElapsedTime();
        if (elapsedskala.asSeconds() <= 5.0f) {
            if (elapsedskala.asSeconds() >= 1.25f * (scaleSteps + 1)) {
                scaleFactorX += 0.25f;
                skala1.setScale(scaleFactorX, scaleFactorX);
                scaleSteps++;
            }
        } else {
            skala1.setScale(0, 0);
            scaleSteps = 0;
            isRightMouseDown = false;  // Resetowanie stanu trzymania myszy
            if (elapsedskala.asSeconds() <= 5.01f) {
                genere_to_pasek();
            }
        }
    }

    // Sprawdzanie, czy skala1 została 'zniknięta'
    if (skala1.getScale().x == 0 && skala1.getScale().y ==0)

    {
    clockskala.restart(); // Restartowanie zegara
    isRightMouseDown = false; // Resetowanie stanu trzymania myszy
    }
    }
//generuje do paska po zniknieciu skaly wartosci miedz zloto itd na podstawie procentow
void Cave::genere_to_pasek()
{
    randomPercent = std::rand() % 10001;
    float FloatRandom = randomPercent / 100;
    if (FloatRandom <= 50)
    {
        // ReadSigns.push_back('I');
        char znak = 'I';
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

            ReadSigns.push_back('I');
            Readvalues.push_back(0);
            for (int j = 0; j < ReadSigns.size(); j++)
            {
                if (ReadSigns[j] == 'I')
                {
                    Readvalues[j] += 1;
                    break;
                }
            }
        }
    }
    else if (FloatRandom > 50 && FloatRandom <= 90)
    {
        // ReadSigns.push_back('R');
        char znak = 'R';
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

            ReadSigns.push_back('R');
            Readvalues.push_back(0);
            for (int j = 0; j < ReadSigns.size(); j++)
            {
                if (ReadSigns[j] == 'R')
                {
                    Readvalues[j] += 1;
                    break;
                }
            }
        }
    }
    else if (FloatRandom > 90 && FloatRandom <= 90.90)
    {
        // ReadSigns.push_back('L');
        char znak = 'D';
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

            ReadSigns.push_back('D');
            Readvalues.push_back(0);
            for (int j = 0; j < ReadSigns.size(); j++)
            {
                if (ReadSigns[j] == 'D')
                {
                    Readvalues[j] += 1;
                    break;
                }
            }
        }
    }
    else
    {
        // ReadSigns.push_back('D');
        char znak = 'L';
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

            ReadSigns.push_back('L');
            Readvalues.push_back(0);
            for (int j = 0; j < ReadSigns.size(); j++)
            {
                if (ReadSigns[j] == 'L')
                {
                    Readvalues[j] += 1;
                    break;
                }
            }
        }
    }
}
//generuje wartości na pasku na dole 
void Cave::addToPasek()
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
                sf::Sprite sprite(obraz1);
                sprite.setPosition(position, 700);
                sprite.setScale(0.15f, 0.15f);
                window.draw(sprite);
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
    //generuje ilośc elementów
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

void Cave::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (openwerehouse)//klasa która otwiera magazyn
            {

                openall->handleMouseEvent(event);
                ReadSigns = openall->getCharValues();
                Readvalues = openall->getIntValues();
            }
        }
        //jeśli naciśniesz spacje generuje Ci skale i jej miejsce obraz i skale
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            isShowing = true;
            int randomX = rand() % 1001 + 100;
            int randomY = rand() % 601;
            int randomRotation = rand() % 181;
            int randomScalesX = rand() % 120 + 50;
            skala1.setRotation(static_cast<float>(randomRotation));
            skala1.setPosition(static_cast<float>(randomX), static_cast<float>(randomY));
            int randomIndex = dis(gen) % 6;
            for (const auto &path : imagePaths)
            {
                sf::Texture texture;
                if (!texture.loadFromFile(path))
                {
                    std::cerr << "Błąd podczas wczytywania tła." << std::endl;
                }
                texturespath.push_back(texture);
            }
            skala1.setTexture(texturespath[randomIndex]);
            sf::FloatRect bounds = skala1.getLocalBounds();
            scaleFactorX = randomScalesX / bounds.width;
            skala1.setScale(scaleFactorX, scaleFactorX);
            std::cout << randomIndex << std::endl;
        }
//gdy naciśniesz skala niech czas leci
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (skala1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                clockskala.restart();
                isRightMouseDown = !isRightMouseDown;
                clockskala.restart();;
            }
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);
               if (skala1.getGlobalBounds().contains(mousePos))
                {
                    isRightMouseDown = true;
                    elapsedskala = clockskala.restart();
                }
            }
        }

        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {

            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosition);

            sf::Vector2f mousePosFloat;

            mousePosFloat = window.mapPixelToCoords(mousePosition);
            sf::Vector2<int> mousePosInt(static_cast<int>(mousePosFloat.x), static_cast<int>(mousePosFloat.y));
if (skala1.getGlobalBounds().contains(mousePos)) {
        isRightMouseDown = false; // Ustawienie flagi na false gdy puścimy skala1
    }


            if (exit.isHoveredButton())
            {
                switchTofarm();//wyjście
            }
            else if (znakzapytania.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                pomocotwarta = true;//znakzapytanie 
            }
            else if (wyjscietablica.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                pomocotwarta = false;//wyjście ze znaku zapytania 
            }
            else if (points.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                openwerehouse = !openwerehouse;
            }
        }
    }
}
//generuje znak zapytania w rogu strony
void Cave::addhelp()
{
    if (!zapytaniezdj.loadFromFile("znakzapytania/zapytanie2.png"))
    {
        std::cerr << "Błąd podczas wczytywania tła." << std::endl;
    }
    znakzapytania.setTexture(zapytaniezdj);
    znakzapytania.setPosition(1080.0f, 660.0f);
    znakzapytania.setScale(0.2f, 0.2f);
}
//generuje tablice po otworzeniu znaku zapytania
void Cave::znakpomocy()
{
    if (!tablicapomoczdj.loadFromFile("znakzapytania/kopalniatablica.png"))
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

void Cave::run()
{
    renderTopasek();
    openall = new Openall(window, ReadSigns, Readvalues);//deklaracja klasy openall
    while (window.isOpen())
    {
        handleEvents();
        render();
        renderskala();
    }
}
//zapisuje do pliku wartości po wyjściu z klasy
void Cave::switchplace()
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

void Cave::render()
{
    window.clear();
    window.draw(background);
    exit.handleMouseInteraction();
    exit.draw();
    window.draw(pasek);
    window.draw(skrzynka);

    if (!openwerehouse)
    {
        addToPasek();
    }
    else
    {

        openall->drawtank();
        openall->addsToPasek();
    }
    if (genereTopasek)
    {
        genere_to_pasek();
        genereTopasek = false;
    }
    addstorage();
    if (isShowing && stop)
    {
        window.draw(skala1);
    }
    std::cout << elapsedskala.asSeconds() << std::endl;
    std::ifstream zlotowkiFile("zlotowki_value.txt");//wychytuje pieniądze z pliku
    zlotowkiText.setString(std::to_string(zlotowkiValue));
    window.draw(zlotowkiText);//wyświetla je
    addhelp();
    if (pomocotwarta)
    {
        znakpomocy();
    }
    window.draw(znakzapytania);
    window.display();
}

void Cave::switchTofarm()
{
    switchplace();
    Game game(window);
    game.run();
}

Cave::~Cave()
{
    delete openall;
}
