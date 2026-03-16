#include "Game.hpp"
#include "Scene/Playing.hpp"
#include "Modules/Entity.hpp"

Playing::Playing(sf::RenderWindow& window) {
    player = std::make_unique<Entity>("./assets/png/Player/Player_", 800);
    enemy = std::make_unique<Entity>("./assets/png/Enemy/Enemy_", 800);
    ball = std::make_unique<Ball>("./assets/png/Ball/Ball_Standard/Ball_Standard_", "./assets/png/Ball/Ball_Collision_Player/Ball_Collision_Player_", "./assets/png/Ball/Ball_Collision_Enemy/Ball_Collision_Enemy_");

    if (!font.openFromFile("./assets/fonts/GameFont.otf")) {
        std::cerr << "Error loading font\n";
    }

    reset(window);
}

void Playing::reset(sf::RenderWindow& window){
    cont = 0;
    playingstate = PlayingState::Start;
    
    player->setPosition((16.f), ((window.getView().getSize().y / 2) - (player->getBounds().size.y / 2)));
    enemy->setPosition((window.getView().getSize().x - enemy->getBounds().size.x - 16.f), ((window.getView().getSize().y / 2) - (enemy->getBounds().size.y / 2)));
    ball->ballReset(window);

    textCenter = std::make_unique<sf::Text>(font, sf::String(textos[0]), 80u);
    textCenter->setFillColor(sf::Color::White);
    textCenter->setPosition(sf::Vector2f((window.getView().getSize().x / 2) - (textCenter->getGlobalBounds().size.x / 2), (window.getView().getSize().y / 2) - (textCenter->getGlobalBounds().size.y / 2)));
    
    pointText = std::make_unique<sf::Text>(font, sf::String("0 | 0"), 40u);
    pointText->setFillColor(sf::Color::White);
    pointText->setPosition(sf::Vector2f((window.getView().getSize().x / 2) - (pointText->getGlobalBounds().size.x / 2), 0.f));

    upPlayer = std::make_unique<sf::Text>(font, sf::String("W"), 40u);
    upPlayer->setFillColor(sf::Color::White);
    upPlayer->setPosition(sf::Vector2f(((player->getBounds().position.x + (player->getBounds().size.x / 2)) - (upPlayer->getGlobalBounds().size.x / 2)), (player->getBounds().position.y - (50.f + upPlayer->getGlobalBounds().size.y))));

    downPlayer = std::make_unique<sf::Text>(font, sf::String("S"), 40u);
    downPlayer->setFillColor(sf::Color::White);
    downPlayer->setPosition(sf::Vector2f(((player->getBounds().position.x + (player->getBounds().size.x / 2)) - (downPlayer->getGlobalBounds().size.x / 2)), (player->getBounds().position.y + player->getBounds().size.y + 50.f)));

    upEnemy = std::make_unique<sf::Text>(font, sf::String("^"), 40u);
    upEnemy->setFillColor(sf::Color::White);
    upEnemy->setPosition(sf::Vector2f(((enemy->getBounds().position.x + (enemy->getBounds().size.x / 2)) - (upEnemy->getGlobalBounds().size.x / 2)), (enemy->getBounds().position.y - (100.f - upEnemy->getGlobalBounds().size.y))));

    downEnemy = std::make_unique<sf::Text>(font, sf::String("v"), 40u);
    downEnemy->setFillColor(sf::Color::White);
    downEnemy->setPosition(sf::Vector2f(((enemy->getBounds().position.x + (enemy->getBounds().size.x / 2)) - (downEnemy->getGlobalBounds().size.x / 2)), (enemy->getBounds().position.y + enemy->getBounds().size.y + 50.f)));
}

void Playing::handleInput(sf::RenderWindow& window, GameState& state, sf::Clock& timer){
    player->collider();
    enemy->collider();
    sf::FloatRect player_bounds = player->getBounds();
    sf::FloatRect enemy_bounds = enemy->getBounds();
    player->handleInput(window, sf::Keyboard::Key::W, sf::Keyboard::Key::S, timer);
    enemy->handleInput(window, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, timer);
    ball->animation(timer);
    switch (playingstate) {
        case PlayingState::Start:
                if(timer.getElapsedTime().asMilliseconds() % 1000 == 0){
                    if(cont <= 3){
                        textCenter->setString(textos[cont]);
                        textCenter->setPosition(sf::Vector2f((window.getView().getSize().x / 2) - (textCenter->getGlobalBounds().size.x / 2), 
                        (window.getView().getSize().y / 2) - (textCenter->getGlobalBounds().size.y / 2)));
                        cont ++;
                    } else {
                        textCenter;
                        playingstate = PlayingState::Go;
                    }
                }
            break;
        case PlayingState::Go:
                ball->move(timer);
            break;
        default:
            break;
    }
    ball->collision(window, player_bounds, enemy_bounds);
    switch (ball->collide){
        case Collision_Ball::Player:
            player->collision = Collision_Entity::True;
            enemy->collision = Collision_Entity::False;
        break;
        case Collision_Ball::Enemy:
            enemy->collision = Collision_Entity::True;
            player->collision = Collision_Entity::False;
        break;
        case Collision_Ball::Not:
            player->collision = Collision_Entity::False;
            enemy->collision = Collision_Entity::False;
        break;
        default:
            break;
    }
}

void Playing::draw(sf::RenderWindow& window) {
    player->draw(window);
    enemy->draw(window);
    window.draw(*pointText);
    
    if (playingstate == PlayingState::Start) {
        window.draw(*textCenter);
        window.draw(*upPlayer);
        window.draw(*downPlayer);
        window.draw(*upEnemy);
        window.draw(*downEnemy);
    } else {
        ball->draw(window);
    }
}