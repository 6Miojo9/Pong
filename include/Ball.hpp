#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Ball {
private:
	std::unique_ptr<sf::Sprite> sprite;
	std::vector<std::vector<sf::Texture>> texture;
	float speed;
	int collider = 0;
	int cont = 1;

public:
	Ball(const std::string& base_path_standard, const std::string& base_path_collision_player, const std::string& base_path_collision_enemy, float speed);

	void setPosition(float x, float y);
	void animation(sf::Clock& clock);
	void collision(sf::FloatRect bounds_payer, sf::FloatRect bounds_enemy);
	void move(float dx, float dy);
	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
};
