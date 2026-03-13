#include "Game.hpp"
#include <iostream>

Entity::Entity(const std::string& base_path, int speed) : speed(speed) {
	texture = animator(base_path, 2);
    sprite = std::make_unique<sf::Sprite>(texture[1]);
}

void Entity::setPosition(float x, float y) {
    sprite->setPosition(sf::Vector2(x, y));
}

void Entity::handleInput(sf::RenderWindow& window, sf::Keyboard::Key key_up, sf::Keyboard::Key key_down, sf::Clock& timer) {
    sf::FloatRect bounds = sprite->getGlobalBounds();
    if (timer.getElapsedTime().asMilliseconds() % 1 == 0){
        if (bounds.position.y > 0.f && sf::Keyboard::isKeyPressed(key_up))
            sprite->move(sf::Vector2(0.f, -0.001f * (speed)));
        if (bounds.position.y < window.getView().getSize().y - bounds.size.y && sf::Keyboard::isKeyPressed(key_down))
            sprite->move(sf::Vector2(0.f, 0.001f * (speed)));
    }
}

void Entity::collider(){
    switch (collision){
        case Collision_Entity::False:
            sprite->setTexture(texture[0]);
            break;
        case Collision_Entity::True:
            sprite->setTexture(texture[1]);
            break;
        default:
            break;
    }
};

void Entity::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}

sf::FloatRect Entity::getBounds() const {
	return sprite->getGlobalBounds();
}