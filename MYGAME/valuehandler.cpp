#include "valuehandler.h"

ValueHandler::ValueHandler(sf::RenderWindow &window, std::vector<char> &wypisz, std::vector<int> &letter, int &zlotowki)
    : window(window), wypisz(wypisz), letter(letter), zlotowki(zlotowki), spriteWidth(50.0f), spriteHeight(50.0f)
{
    valueMap = {
        {'P', 1},
        {'M', 5},
        {'T', 20},
        {'C', 55},
        {'S', 150},
        {'J', 40},
        {'G', 70},
        {'Z', 100},
        {'A', 350},
        {'E', 600},
        {'F', 850},
        {'I', 5},
        {'R', 20},
        {'L', 100},
        {'D', 300},
        {'W', 10000},
        {'K', 20000},
        {'U', 30000},
    };
}

void ValueHandler::handleRightClick(const sf::Vector2f &mousePos)
{
    int position = 270;
    int interval = 150;

    for (size_t i = 0; i < wypisz.size(); ++i)
    {
        sf::FloatRect spriteBounds(position, 690, spriteWidth, spriteHeight);

        if (spriteBounds.contains(mousePos))
        {
            int value = valueMap[wypisz[i]];
            zlotowki += value;

            if (letter[i] > 0)
            {
                letter[i]--;
                if (letter[i] == 0)
                {
                    wypisz.erase(wypisz.begin() + i);
                    letter.erase(letter.begin() + i);
                }
            }

            break;
        }

        position += interval;
    }
}
