#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class TextureManagement
{
public:
	TextureManagement();
	static sf::Texture LoadTextFromPath(sf::Texture& text, sf::String path);
	static int GetAmountOfFrames(sf::String path);
	static sf::IntRect GetFrameSize(sf::FloatRect rect);
	static sf::Vector2i GetFrameSizeFromName(sf::String path);
private:
	static sf::String getFilenameFromPath(sf::String path);

};

