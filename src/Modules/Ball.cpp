#include "Game.hpp"
#include <iostream>


Ball::Ball(
	const std::string& base_path_standard,
	const std::string& base_path_collision_player,
	const std::string& base_path_collision_enemy
) {
	texture.push_back(animator(base_path_standard, 23));
	texture.push_back(animator(base_path_collision_player, 23));
	texture.push_back(animator(base_path_collision_enemy, 23));
	sprite = std::make_unique<sf::Sprite>(texture[0][0]);
}

void Ball::setPosition(float x, float y) {
	sprite->setPosition(sf::Vector2(x, y));
}

void Ball::animation(sf::Clock& timer){
	if(timer.getElapsedTime().asMilliseconds() % (1000 / 23) == 0){
		if(cont != 22){
			cont ++;
		} else {
			cont = 0;
		}
	}

	switch (collide){
		case Collision_Ball::Not:
			sprite->setTexture(texture[0][cont]);
			break;
		case Collision_Ball::Player:
			sprite->setTexture(texture[1][cont]);
			break;
		case Collision_Ball::Enemy:
			sprite->setTexture(texture[2][cont]);
			break;
		default:
			break;
	}
};

void Ball::collision(sf::RenderWindow& window, sf::FloatRect& bounds_payer, sf::FloatRect& bounds_enemy) {
    if ((getBounds().position.y < 0 && direction_y < 0) || 
	(getBounds().position.y > (window.getView().getSize().y - getBounds().size.y) && direction_y > 0)) {
        direction_y = -direction_y;
    }

	if(getBounds().findIntersection(bounds_payer) && (bounds_payer.position.x + bounds_payer.size.x) >= getBounds().position.x && getBounds().position.x >= (bounds_payer.position.x + bounds_payer.size.x - 16.f) && 
	direction_x < 0.f){
		direction_x = -direction_x;
		collide = Collision_Ball::Player;
	}

	if(getBounds().findIntersection(bounds_enemy) && (getBounds().position.x + getBounds().size.x) >= bounds_enemy.position.x && (bounds_enemy.position.x + 16.f) >= (getBounds().position.x + getBounds().size.x) && 
	direction_x > 0.f){
		direction_x = -direction_x;
		collide = Collision_Ball::Enemy;
	}

	if (getBounds().position.x < 0) {
		ballReset(window);
	}

	if (getBounds().position.x > (window.getView().getSize().x - getBounds().size.x)) {
		ballReset(window);
    }
}

void Ball::ballReset(sf::RenderWindow& window){
	sprite->setPosition(sf::Vector2(window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f));
	collide = Collision_Ball::Not;
	speed = 3000;
};

void Ball::move(sf::Clock& timer) {
	if (timer.getElapsedTime().asMilliseconds() % 1 == 0) {
		sprite->move(sf::Vector2f(direction_x * (speed/1000), direction_y * (speed/1000)));
	}
	if (timer.getElapsedTime().asMilliseconds() % 1 == 0 && speed < 80000) {		
		speed = speed + 1;
	}
}

void Ball::draw(sf::RenderWindow& window) {
	window.draw(*sprite);
}

sf::FloatRect Ball::getBounds() const {
	return sprite->getGlobalBounds();
}