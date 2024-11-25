#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TextureManagement
{
public:
	TextureManagement();
	static sf::Texture LoadTextFromPath(sf::Texture& text, sf::String path);
	static sf::Vector2i GetFrameSize(const std::string& filename);
	static std::string SearchForItemInFolder(std::string folderPath, std::string inputName);
	static std::vector<sf::Texture> GetTexturesFromAtlas(std::string filePath, int numOfTextures);
	static int GetFrameAmountFromAtlas(sf::Texture& txr, sf::Vector2i frameSize, int animInAtlasId);
private:
	static sf::String getFilenameFromPath(sf::String path);
	static bool IsEmptyFrame(sf::Texture& txr, sf::Vector2i frameSize, sf::Vector2i pos);
};