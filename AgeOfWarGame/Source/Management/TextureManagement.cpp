#include "TextureManagement.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <regex>

namespace fs = std::filesystem;

TextureManagement::TextureManagement()
{
}


sf::Texture TextureManagement::LoadTextFromPath(sf::Texture& text, sf::String path) {
    if (!text.loadFromFile(path)) {
        std::cerr << "Error loading texture from path: " << path.toAnsiString() << std::endl;
        return sf::Texture();
    }
}

sf::Vector2i TextureManagement::GetFrameSize(const std::string& filename)
{
    size_t pos = filename.find('_'); // Find the underscore separating name and resolution
    if (pos != std::string::npos) {
        std::string resolutionPart = filename.substr(pos + 1); // Extract the part after '_'

        size_t xPos = resolutionPart.find('x'); // Look for the 'x' in the resolution
        if (xPos != std::string::npos) {
            int width = std::stoi(resolutionPart.substr(0, xPos)); // Extract width
            int height = std::stoi(resolutionPart.substr(xPos + 1)); // Extract height
            return sf::Vector2i(width, height); // Return as sf::Vector2i
        }
    }

    // If no resolution in the filename, load the texture and return its height
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        return sf::Vector2i(texture.getSize().y, texture.getSize().y); // Return width and height of the texture
    }

    // Debug message for when the texture cannot be loaded
    std::cerr << "Failed to load texture from file: " << filename << std::endl;

    return sf::Vector2i(0, 0); // Return (0, 0) if the texture cannot be loaded or no resolution found
}

std::string TextureManagement::SearchForItemInFolder(std::string folderPath, std::string inputName) {
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Invalid folder path: " << folderPath << std::endl;
        return "";
    }

    std::transform(inputName.begin(), inputName.end(), inputName.begin(), ::tolower);

    for (const fs::directory_entry& entry : fs::directory_iterator(folderPath)) {
        std::string itemPath = entry.path().string();
        std::string lowerItemPath = itemPath;
        std::transform(lowerItemPath.begin(), lowerItemPath.end(), lowerItemPath.begin(), ::tolower);

        if (lowerItemPath.find(inputName) != std::string::npos) {
            //std::cerr << "Successfully found: " << itemPath << std::endl;
            return itemPath;
        }
    }

    std::cerr << "Could not find: " << inputName << std::endl;
    return "";
}
std::vector<sf::Texture> TextureManagement::GetTexturesFromAtlas(std::string filePath, int numOfTextures)
{
    return std::vector<sf::Texture>();
}
int TextureManagement::GetFrameAmountFromAtlas(sf::Texture& txr, sf::Vector2i frameSize, int animInAtlasId)
{
    sf::Vector2u textureSize = txr.getSize();

    int amountOfFrames = 0;
    int amountOfAnims = txr.getSize().y / frameSize.y;
    sf::Vector2i searchPos = sf::Vector2i(0, (animInAtlasId - 1) * frameSize.y);
    for (int i = 0; i < txr.getSize().x / frameSize.x; ++i) {
        if (IsEmptyFrame(txr, frameSize, searchPos)) return amountOfFrames;
        else { 
            searchPos.x += frameSize.x;
            amountOfFrames++; 
        }
    }
}

sf::String TextureManagement::getFilenameFromPath(sf::String path)
{
    return std::filesystem::path(path).filename().string();
}

bool TextureManagement::IsEmptyFrame(sf::Texture& txr, sf::Vector2i frameSize, sf::Vector2i pos) {
    sf::Image sheetImg = txr.copyToImage();

    int startX = std::max(0, pos.x);
    int startY = std::max(0, pos.y);
    int endX = std::min(pos.x + frameSize.x, static_cast<int>(txr.getSize().x));
    int endY = std::min(pos.y + frameSize.y, static_cast<int>(txr.getSize().y));

    // Iterate over each pixel in the specified area
    for (int x = startX; x < endX; ++x) {
        for (int y = startY; y < endY; ++y) {
            sf::Color color = sheetImg.getPixel(x, y);

            if (color.a != 0) {
                return false;
            }
        }
    }

    return true;
}
