#include "Entity.hpp"
#include <iostream>
#include "Animator.hpp"

Entity::Entity(const std::string& caminhoTextura, float velocidade) : speed(velocidade) {
	texture = animator(caminhoTextura, 2);
    sprite = std::make_unique<sf::Sprite>(texture[0]);
}

void Entity::setPosition(float x, float y) {
    sprite->setPosition(sf::Vector2(x, y));
}

void Entity::move(float dx, float dy) {
    sprite->move(sf::Vector2(dx, dy));
}

void Entity::handleInput(float window_y, sf::Keyboard::Key key_up, sf::Keyboard::Key key_down) {
    sf::FloatRect bounds = sprite->getGlobalBounds();
    if (bounds.position.y > 0.f)
        if (sf::Keyboard::isKeyPressed(key_up))
            sprite->move(sf::Vector2(0.f, -speed));
    if (bounds.position.y < window_y - bounds.size.y)
        if (sf::Keyboard::isKeyPressed(key_down))
            sprite->move(sf::Vector2(0.f, speed));
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}

sf::FloatRect Entity::getBounds() const {
    return sprite->getGlobalBounds();
}
