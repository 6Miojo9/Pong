#include "Game.hpp"
#include "Scene/Playing.hpp"
#include "Modules/Entity.hpp"

Playing::Playing(sf::RenderWindow& window) {
    player = std::make_unique<Entity>("./assets/png/Player/Player_", 800);
    enemy = std::make_unique<Entity>("./assets/png/Enemy/Enemy_", 800);
    ball = std::make_unique<Ball>(
        "./assets/png/Ball/Ball_Standard/Ball_Standard_",
        "./assets/png/Ball/Ball_Collision_Player/Ball_Collision_Player_",
        "./assets/png/Ball/Ball_Collision_Enemy/Ball_Collision_Enemy_"
    );
    player->setPosition(
        (16.f),
        ((window.getView().getSize().y / 2) - (player->getBounds().size.y / 2))
    );
    enemy->setPosition(
        (window.getView().getSize().x - enemy->getBounds().size.x - 16.f),
        ((window.getView().getSize().y / 2) - (enemy->getBounds().size.y / 2))
    );
    ball->setPosition(
        ((window.getView().getSize().x / 2) - (ball->getBounds().size.x / 2)), 
        ((window.getView().getSize().y / 2) - (ball->getBounds().size.y / 2))
    );
}

void Playing::handleInput(sf::RenderWindow& window, GameState& state, sf::Clock& timer){
    player->handleInput(window, sf::Keyboard::Key::W, sf::Keyboard::Key::S, timer);
    enemy->handleInput(window, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, timer);
    player->collider();
    enemy->collider();
    ball->animation(timer);
    sf::FloatRect player_bounds = player->getBounds();
    sf::FloatRect enemy_bounds = enemy->getBounds();
    ball->move(timer);
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
    ball->draw(window);
}