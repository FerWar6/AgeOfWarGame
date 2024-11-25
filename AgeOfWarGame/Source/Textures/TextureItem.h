#pragma once
#include <SFML/Graphics.hpp>
class TextureItem
{
public:
	TextureItem(std::string path);
	sf::Texture& GetTexture();
	std::string& GetName();
	sf::Vector2i GetSize();
	bool IsSheet();
private:
	sf::Texture texture;
	sf::Vector2i frameSize;
	std::string name;
	bool isSheet;
};
