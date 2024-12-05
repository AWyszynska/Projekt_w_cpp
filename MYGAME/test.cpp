#include <SFML/Graphics.hpp>
#include "openall.h"
int main()
{
    // Utworzenie okna o wymiarach 800x600
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML window");

    // Ustawienie koloru tła
    sf::Color backgroundColor = sf::Color::Blue;
std::vector <char> wartoscichar = {'P','K','Z','A','E','F','G','J','T','C','S'};
std::vector<int> wartosciint = {12,3,6,7,5,3,1,2,3,4,8,7};
    // Główna pętla programu
    Openall openall(window,wartoscichar,wartosciint);
    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
while (window.pollEvent(event))
{
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::MouseButtonPressed) {
        openall.handleMouseEvent(event); 
            wartoscichar = openall.getCharValues();
            wartosciint = openall.getIntValues();
}
 }       // Czyszczenie okna kolorem tła
        window.clear(backgroundColor);
            openall.drawtank();
            openall.addsToPasek();
                for(int i =0;i<wartoscichar.size();i++){
        std::cout<<wartoscichar[i];
    }
        // Wyświetlenie zawartości okna
        window.display();
    }

    return 0;
}

