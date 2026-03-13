#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

std::vector<sf::Texture> animator(const std::string& base_path, int amount);

bool collider(const sf::FloatRect& bounds_entity_1, const sf::FloatRect& bounds_entity_2);