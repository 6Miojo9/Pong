#include "Ball.hpp"
#include <iostream>
#include "Animator.hpp"
#include "Collider.hpp"

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

	switch (collide){
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

void Ball::collision(float window_x, float window_y, sf::FloatRect& bounds_payer, sf::FloatRect& bounds_enemy) {
    sf::FloatRect bounds_ball = sprite->getGlobalBounds();

    if (bounds_ball.position.y < 0 || bounds_ball.position.y > (window_y - bounds_ball.size.y)) {
        direction_y = -direction_y;
    }

    if (collider(bounds_ball, bounds_payer) || collider(bounds_ball, bounds_enemy)) {
        direction_x = -direction_x;
    }

	if (bounds_ball.position.x < 0) {
        sprite->setPosition(sf::Vector2(window_x / 2.f, window_y / 2.f));
    }

	if (bounds_ball.position.x > (window_x - bounds_ball.size.x)) {
        sprite->setPosition(sf::Vector2(window_x / 2.f, window_y / 2.f));
    }
}

void Ball::move() {
	sprite->move(sf::Vector2((speed * direction_x), (speed * direction_y)));
}

void Ball::draw(sf::RenderWindow& window) {
	window.draw(*sprite);
}

sf::FloatRect Ball::getBounds() const {
	return sprite->getGlobalBounds();
}