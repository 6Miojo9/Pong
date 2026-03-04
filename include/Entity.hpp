#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
private:
    std::unique_ptr<sf::Sprite> sprite;
    std::vector<sf::Texture> texture;
    float speed;

public:
    Entity(const std::string& caminhoTextura, float velocidade);

    void setPosition(float x, float y);
    void move(float dx, float dy);
    void handleInput(float window_y, sf::Keyboard::Key key_up, sf::Keyboard::Key key_down);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
