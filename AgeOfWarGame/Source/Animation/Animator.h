#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Animator
{
public:
	Animator(sf::Sprite& sprite);
	void UpdateAnim();
	void AddAnimation(sf::String path);
	std::vector<Animation>& GetAnimations();
private:
	sf::Sprite& sprite;
	std::vector<Animation> animations;
};
