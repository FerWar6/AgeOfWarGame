#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Animator;

class Animation
{
public:
	Animation(sf::String path, sf::String name);
	sf::IntRect GetAnimationFrame();
	sf::Texture& GetTexture();
	sf::Vector2i GetFrameSize();
	sf::String GetName();
	void ResetAnimation();
private:
	void UpdateFrame();
	sf::String name;
	sf::Texture fullTexture;
	sf::Vector2i frameSize;
	int amountOfFrames;
	int currentFrame;
};