#include "Game.hpp"
#include "Scene/Menu.hpp"
#include "Modules/Button.hpp"

Menu::Menu(sf::RenderWindow& window) {
    playButton = std::make_unique<Button>("./assets/png/Button/Button_", "Play");
    exitButton = std::make_unique<Button>("./assets/png/Button/Button_", "Exit");
    playButton->setPosition(
        ((window.getView().getSize().x / 2) - playButton->getBounds().size.x / 2),
        ((window.getView().getSize().y / 2) - playButton->getBounds().size.y - 10.f)
    );
    exitButton->setPosition(
        ((window.getView().getSize().x / 2) - playButton->getBounds().size.x / 2),
        ((window.getView().getSize().y / 2) + 10.f)
    );
}

void Menu::handleInput(sf::RenderWindow& window, GameState& state) {
    playButton->onHover(window);
    exitButton->onHover(window);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (playButton->getBounds().contains(mouseWorld)) {
            state = GameState::Playing;
        }
        if (exitButton->getBounds().contains(mouseWorld)) {
            window.close();
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    playButton->draw(window);
    exitButton->draw(window);
}
