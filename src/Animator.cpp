#include "Animator.hpp"
#include <iostream>

std::vector<sf::Texture> animator(const std::string& caminhoBase, int quantidade) {
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= quantidade; i++) {
        sf::Texture tex;
        std::string caminho = caminhoBase + std::to_string(i) + ".png";
        if (!tex.loadFromFile(caminho)) {
            std::cerr << "Erro ao carregar: " << caminho << std::endl;
        } else {
            frames.push_back(std::move(tex));
        }
    }
    return frames;
}