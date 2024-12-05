#include "timerbar.h"

TimerBar::TimerBar(float totalTime, float width, float height, const sf::Color &color)
    : totalTime(totalTime), width(width), height(height)
{
    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(color);
}

void TimerBar::update()
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    float remainingTime = std::max(totalTime - elapsedTime, 0.0f);
    float newWidth = (remainingTime / totalTime) * width;
    bar.setSize(sf::Vector2f(newWidth, height));
}

void TimerBar::draw(sf::RenderWindow &window)
{
    window.draw(bar);
}

void TimerBar::setPosition(float x, float y)
{
    bar.setPosition(x, y);
}

void TimerBar::setTotalTime(float newTotalTime)
{
    totalTime = newTotalTime;
    clock.restart();
}

bool TimerBar::isTimeUp()
{
    return clock.getElapsedTime().asSeconds() >= totalTime;
}

void TimerBar::addTime(float additionalTime)
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    totalTime += additionalTime;
    if (totalTime - elapsedTime < 0)
    {
        totalTime = elapsedTime;
    }
}

void TimerBar::setRemainingTime(float time)
{
    remainingTime = time;
}

float TimerBar::getRemainingTime() const
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    float remainingTime = totalTime - elapsedTime;
    return remainingTime > 0 ? remainingTime : 0;
}

void TimerBar::reset()
{
    clock.restart();
}
