#pragma once

#include <SFML/Graphics.hpp>

class TimerBar
{
private:
    sf::RectangleShape bar;
    sf::Clock clock;
    float totalTime;
    float width, height;
    float remainingTime;

public:
    void setRemainingTime(float time);
    TimerBar(float totalTime, float width, float height, const sf::Color &color);
    void setTotalTime(float newTotalTime);
    void update();
    void addTime(float additionalTime);
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    bool isTimeUp();
    void reset();
    float getRemainingTime() const;
};
