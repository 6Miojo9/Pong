#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameState.hpp" 

enum class PlayingState{ Start, Go };

class Playing {
public:
    Playing(sf::RenderWindow& window);
    void reset(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, GameState& state, sf::Clock& timer);
    void draw(sf::RenderWindow& window);

private:
    PlayingState playingstate = PlayingState::Start;
    std::unique_ptr<Entity> player;
    std::unique_ptr<Entity> enemy;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<sf::Text> textCenter, pointText, upPlayer, downPlayer, upEnemy, downEnemy;
    sf::Font font;
    int cont = 1;
    std::vector<std::string> textos = {"3!", "2!", "1!", "Go!!!"};
};
