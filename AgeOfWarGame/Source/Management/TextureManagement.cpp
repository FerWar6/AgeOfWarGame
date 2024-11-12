#include "TextureManagement.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <regex>

TextureManagement::TextureManagement()
{
}


sf::Texture TextureManagement::LoadTextFromPath(sf::Texture& text, sf::String path) {
    if (!text.loadFromFile(path)) {
        std::cerr << "Error loading texture from path: " << path.toAnsiString() << std::endl;
        return sf::Texture();
    }
}

int TextureManagement::GetAmountOfFrames(sf::String path)
{
    return 10;
}

sf::IntRect TextureManagement::GetFrameSize(sf::FloatRect rect)
{
    sf::IntRect output;
    output.width = rect.height;
    output.height = rect.height;
    return output;
}

sf::Vector2i TextureManagement::GetFrameSizeFromName(sf::String path)
{
    sf::String fileName = getFilenameFromPath(path);
    return sf::Vector2i(45,45);
}

sf::String TextureManagement::getFilenameFromPath(sf::String path)
{
    return std::filesystem::path(path).filename().string();
}
