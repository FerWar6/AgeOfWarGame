#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Animator;

class Animation
{
public:
	Animation(sf::String path);
	sf::IntRect GetAnimationFrame();
	sf::Texture& GetTexture();
	void ResetAnimation();
private:
	sf::Texture fullTexture;
	void UpdateFrame();
	sf::Vector2i frameSize;
	int numberOfFrames;
	int currentFrame;
};