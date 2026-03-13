#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Button {
public:
    Button(const std::string& base_path, const std::string& text);

    void setPosition(float x, float y);
    void setTexture(int index);
    sf::FloatRect getBounds() const;
    bool onClick(sf::RenderWindow& window);
    void onHover(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<sf::Text> label;
    sf::Font font;
    std::vector<sf::Texture> textures;
    std::unique_ptr<sf::Sprite> sprite;
};