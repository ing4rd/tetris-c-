#include "../head/resources.h"
#include <filesystem>
#include <iostream>

Resources::Resources()
{
    namespace fs = std::filesystem;

    m_font.loadFromFile("assets/font.ttf");

    fs::path dirPath("assets/images");

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        std::cout << "Error while looking for image path!\n";
    }

    for (const auto &entry : fs::directory_iterator(dirPath))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            sf::Texture texture;
            if (texture.loadFromFile(entry.path().string()))
            {
                m_textures[filename] = texture;
            }
            else
            {
                std::cout << "Error reading image!\n";
            }
        }
    }
}