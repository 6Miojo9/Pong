#include "Ball.hpp"
#include <iostream>
#include "Animator.hpp"

Ball::Ball(const std::string& base_path_standard, const std::string& base_path_collision_player, const std::string& base_path_collision_enemy, float speed) : speed(speed) {
	texture.push_back(animator(base_path_standard, 23));
	texture.push_back(animator(base_path_collision_player, 23));
	texture.push_back(animator(base_path_collision_enemy, 23));
	sprite = std::make_unique<sf::Sprite>(texture[0][0]);
}

void Ball::setPosition(float x, float y) {
	sprite->setPosition(sf::Vector2(x, y));
}

void Ball::animation(sf::Clock& clock){
	if(clock.getElapsedTime().asMilliseconds() % (1000 / 23) == 0){
		if(cont != 22){
			cont ++;
		} else {
			cont = 0;
		}
	}

	switch (collider){
		case 0:
			sprite->setTexture(texture[0][cont]);
			break;
		case 1:
			sprite->setTexture(texture[1][cont]);
			break;
		case 2:
			sprite->setTexture(texture[2][cont]);
			break;
		default:
			break;
	}
};

void Ball::move(float dx, float dy) {
	sprite->move(sf::Vector2(dx, dy));
}

void Ball::draw(sf::RenderWindow& window) {
	window.draw(*sprite);
}

sf::FloatRect Ball::getBounds() const {
	return sprite->getGlobalBounds();
}