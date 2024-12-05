#ifndef VALUEHANDLER_H
#define VALUEHANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <sstream>
class ValueHandler
{
public:
    ValueHandler(sf::RenderWindow &window, std::vector<char> &wypisz, std::vector<int> &letter, int &zlotowki);

    void handleRightClick(const sf::Vector2f &mousePos);

private:
    sf::RenderWindow &window;
    std::vector<char> &wypisz;
    std::vector<int> &letter;
    int &zlotowki;
    const float spriteWidth;
    const float spriteHeight;

    std::unordered_map<char, int> valueMap;
};

#endif // VALUEHANDLER_H
