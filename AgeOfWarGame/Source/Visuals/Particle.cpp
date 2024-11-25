#include "Particle.h"
Particle::Particle(sf::Vector2f pos, sf::Texture& txr)
	:	Object(pos, sf::Vector2f(0,0)),
	particleTxr(txr)
{
	particleSprite.setTexture(particleTxr);
}

void Particle::UpdateObj()
{
}

void Particle::RenderObj(sf::RenderWindow& window)
{
	particleSprite.setPosition(GetPos());
	window.draw(particleSprite);
}
