#include "TextureLoader.h"
#include "TextureManagement.h"

#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

TextureLoader::TextureLoader()
{
	std::string texturePath = "Assets/Units/";
	LoadTextures(texturePath);
}

void TextureLoader::LoadTextures(std::string& path)
{
    // Loop through all files in the specified folder
    for (const auto& entry : fs::directory_iterator(path)) {
        std::string filePath = entry.path().string();

        // Check if the file is a .png or .jpg (can add more extensions if needed)
        if (filePath.size() >= 4 &&
            (filePath.compare(filePath.size() - 4, 4, ".png") == 0 ||
                filePath.compare(filePath.size() - 4, 4, ".jpg") == 0))
        {
            sf::Texture texture;
            if (texture.loadFromFile(filePath)) {
                std::string textureName = entry.path().stem().string();  // Get the filename without the extension
                AddTexture(texture, textureName);  // Add the texture to the list
            }
            else {
                std::cerr << "Failed to load texture: " << filePath << std::endl;
            }
        }
    }
}

void TextureLoader::AddTexture(sf::Texture t, std::string n)
{
	loadedTextures.emplace_back(t, n);
}
