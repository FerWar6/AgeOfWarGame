#pragma once

#include "Objects/Object.h"
#include <SFML/Graphics.hpp>
class Particle : public Object
{
public:
	Particle(sf::Vector2f pos, sf::Texture& txr);
private:
	void UpdateObj() override;
	void RenderObj(sf::RenderWindow& window) override;
	sf::Texture& particleTxr;
	sf::Sprite particleSprite;
	float lifeTime;
};

