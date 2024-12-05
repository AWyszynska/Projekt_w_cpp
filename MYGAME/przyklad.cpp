#include <SFML/Graphics.hpp>
#include <iostream>

class State {
public:
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual State* nextState() { return nullptr; }  // Dodaj domyślną implementację, aby uniknąć błędów kompilacji
    virtual ~State() {}
};

class GameWindow : public State {
public:
    void handleEvents(sf::RenderWindow& window) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void update() override {
        // Tutaj dodaj logikę gry
    }

    void render(sf::RenderWindow& window) override {
        window.clear();
        // Tutaj dodaj rysowanie elementów gry
        window.display();
    }

    State* nextState() override {
        // Zwracamy wskaźnik na nowy stan lub nullptr, jeśli nie ma przejścia do innego stanu
        return nullptr;
    }
};

class MenuWindow : public State {
public:
    void handleEvents(sf::RenderWindow& window) override {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    // Przełącz na stan gry
                    nextState_ = std::make_unique<GameWindow>();
                }
            }
        }
    }

    void update() override {
        // Aktualizacja logiki menu
    }

    void render(sf::RenderWindow& window) override {
        window.clear();
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();
    }

    State* nextState() override {
        // Zwracamy wskaźnik na nowy stan lub nullptr, jeśli nie ma przejścia do innego stanu
        return nextState_.get();
    }

private:
    sf::RectangleShape startButton;
    sf::Text startButtonText;
    std::unique_ptr<State> nextState_;

    // Inne dane i metody związane z menu
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu", sf::Style::Close);
    window.setFramerateLimit(60);

    std::unique_ptr<State> currentState = std::make_unique<MenuWindow>();

    while (window.isOpen()) {
        currentState->handleEvents(window);
        currentState->update();
        currentState->render(window);

        State* next = currentState->nextState();
        if (next) {
            // Przełącz do nowego stanu
            currentState = std::unique_ptr<State>(next);
        }
    }

    return 0;
}



