#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameState.hpp" 

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, GameState& state);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<Button> playButton;
    std::unique_ptr<Button> exitButton;
};
