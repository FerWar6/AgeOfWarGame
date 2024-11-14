#pragma once
#include <SFML/Graphics.hpp>

#include "Management/TextureItem.h"
class TextureLoader
{
public:
	TextureLoader();
	void LoadTextures(std::string& path);
	void AddTexture(sf::Texture t, std::string n);
private:
	std::vector<TextureItem> loadedTextures;
};