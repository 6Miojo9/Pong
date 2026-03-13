#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

enum class Collision_Ball { Not, Player, Enemy };

class Ball {
	
	private:
		std::unique_ptr<sf::Sprite> sprite;
		std::vector<std::vector<sf::Texture>> texture;
		int speed = 3000, cont = 0;
		float direction_x = -0.1f, direction_y = 0.1f;

	public:
		Collision_Ball collide = Collision_Ball::Not;

		Ball(const std::string& base_path_standard, const std::string& base_path_collision_player, const std::string& base_path_collision_enemy);

		void setPosition(float x, float y);
		void animation(sf::Clock& timer);
		void collision(sf::RenderWindow& window, sf::FloatRect& bounds_payer, sf::FloatRect& bounds_enemy);
		void ballReset(sf::RenderWindow& window);
		void move(sf::Clock& timer);
		void draw(sf::RenderWindow& window);

		sf::FloatRect getBounds() const;
};