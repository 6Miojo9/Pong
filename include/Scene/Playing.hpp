#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameState.hpp" 

class Playing {
public:
    Playing(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, GameState& state, sf::Clock& timer);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<Entity> player;
    std::unique_ptr<Entity> enemy;
    std::unique_ptr<Ball> ball;
};
