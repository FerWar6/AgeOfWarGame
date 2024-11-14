#pragma once
#include <SFML/Graphics.hpp>
class TextureItem
{
public:
	TextureItem(sf::Texture texture, std::string name);
	sf::Texture& GetTexture();
	std::string& GetName();
private:
	sf::Texture texture;
	std::string name;
};
