#pragma once

#include <SFML/Graphics.hpp>
#include "Textures/TextureLoader.h"
class Background
{
public:
	Background(TextureLoader* txrLdr);
	void Drawbg(sf::RenderWindow& win);
private:

	sf::Texture& bgTexture;
	sf::Sprite bgSprite;
	bool posSet;

	sf::Texture& groundTexture;
	sf::Sprite groundSprite;
};

