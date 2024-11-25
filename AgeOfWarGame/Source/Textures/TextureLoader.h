#pragma once
#include <SFML/Graphics.hpp>

#include "Textures/TextureItem.h"
#include "Textures/SpriteSheet.h"
class TextureLoader
{
public:
	TextureLoader();
	void LoadTextures(std::string& path);
	void LoadSpriteSheets();
	void AddTexture(std::string path);
	sf::Texture& GetTexture(std::string name);
	TextureItem& GetTextureItem(std::string name);
	sf::Vector2i GetTextureSize(std::string name);
	std::vector<TextureItem>& GetLoadedTextures();

	void AddSpriteSheet(TextureItem& txr);
	SpriteSheet& GetSpriteSheet(std::string name);
	std::vector<SpriteSheet>& GetSpriteSheets();
private:
	std::vector<TextureItem> loadedTextures;
	std::vector<SpriteSheet> spriteSheets;
};