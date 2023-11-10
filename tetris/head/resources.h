#pragma once
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

struct Resources
{
    Resources();
    std::unordered_map<std::string, sf::Texture> m_textures;
    sf::Font m_font;
};