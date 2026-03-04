#include "Animator.hpp"
#include <iostream>

std::vector<sf::Texture> animator(const std::string& base_path, int amount) {
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= amount; i++) {
        sf::Texture text;
        std::string path = base_path + std::to_string(i) + ".png";
        if (!text.loadFromFile(path)) {
            std::cerr << "Error loading: " << path << std::endl;
        } else {
            frames.push_back(std::move(text));
        }
    }
    return frames;
}