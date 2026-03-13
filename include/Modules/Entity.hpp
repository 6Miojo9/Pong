#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

enum class Collision_Entity { False, True };

class Entity {
    private:
        std::unique_ptr<sf::Sprite> sprite;
        std::vector<sf::Texture> texture;
        int speed;

    public:
        Collision_Entity collision = Collision_Entity::False;
        Entity(const std::string& base_path, int speed);

        void setPosition(float x, float y);
        void handleInput(sf::RenderWindow& window, sf::Keyboard::Key key_up, sf::Keyboard::Key key_down, sf::Clock& timer);
        void collider();
        void draw(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;
};
