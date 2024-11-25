#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "Textures/SpriteSheet.h"
class Animator;

class Animation
{
public:
	Animation(sf::String name, sf::Texture& txr, sf::Vector2i frSize, bool loop, std::function<void()> onEnd);
	Animation(sf::String name, int animId, SpriteSheet& sheet, bool loop, std::function<void()> onEnd);
	sf::IntRect GetAnimationFrame();
	sf::Texture& GetTexture();
	sf::Vector2i GetFrameSize();
	std::string GetName();
	void ResetAnimation();
	void OnAnimEnd();
private:
	std::function<void()> OnAnimationEnd;
	void UpdateFrame();
	sf::String name;
	sf::Texture& fullTexture;
	sf::Vector2i frameSize;
	sf::Vector2i posOnSheet;
	int amountOfFrames;
	int currentFrame;
	bool loopAnimation;
	bool onLastFrame = false;
};