#include "TextureItem.h"

TextureItem::TextureItem(sf::Texture t, std::string n)
	: texture(t), name(n)
{}

sf::Texture& TextureItem::GetTexture()
{
	return texture;
}

std::string& TextureItem::GetName()
{
	return name;
}

