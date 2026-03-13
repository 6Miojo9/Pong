#include "Game.hpp"

Button::Button(const std::string& base_path, const std::string& text) {
    textures = animator(base_path, 3);
    sprite = std::make_unique<sf::Sprite>(textures[0]);
    sprite->setTexture(textures[0]);
    if (!font.openFromFile("./assets/fonts/GameFont.ttf")) {
        std::cerr << "Error loading font\n";
    }
    label = std::make_unique<sf::Text>(font, sf::String(text), 24u);
    label->setFillColor(sf::Color::White);
}

void Button::setPosition(float x, float y) {
	sprite->setPosition(sf::Vector2f(x, y));
    sf::FloatRect bounds_label = label->getGlobalBounds();
    sf::FloatRect bounds_sprite = sprite->getGlobalBounds();
    label->setPosition(sf::Vector2f(x + ((bounds_sprite.size.x - bounds_label.size.x) / 2), y + ((bounds_sprite.size.y - bounds_label.size.y) / 2) - 5));
}

void Button::setTexture(int index){
    sprite->setTexture(textures[index]);
}

sf::FloatRect Button::getBounds() const {
    return sprite->getGlobalBounds();
}

bool Button::onClick(sf::RenderWindow& window) {
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return getBounds().contains(mouseWorld) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::onHover(sf::RenderWindow& window) {
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if(getBounds().contains(mouseWorld)) {
        sprite->setTexture(textures[1]);
    } else {
        sprite->setTexture(textures[0]);
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
    window.draw(*label);
}
