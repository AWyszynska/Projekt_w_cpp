#include <SFML/Graphics.hpp>
#include <iostream>

#include "gra.h"
#include "guzik.h"
#include "menu.h"
#include "garden.h"
#include "guzikwarz.h"
#include "shop.h"
#include "guziksklep.h"
#include "orchard.h"
#include "hodowla.h"
#include "valuehandler.h"
//#include "HoverDisplayss.h"
int main()
{

     Menu menu;
     menu.run();

    //sf::RenderWindow window(sf::VideoMode(1200, 800), "handlarz");
   // window.setFramerateLimit(60);

    //static Hodowla hodowla(window);
   // hodowla.run();

    return 0;
}
