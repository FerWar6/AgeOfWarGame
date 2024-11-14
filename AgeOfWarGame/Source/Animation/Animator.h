#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Animator
{
public:
	Animator(sf::Sprite& sprite);
	void UpdateAnim();
	void SetAnimation(sf::String animName);
	void AddAnimation(sf::String path, sf::String animationName);
	std::vector<Animation>& GetAnimations();
private:
	void SetFirstAnim();
	sf::Sprite& sprite;
	std::vector<Animation> animations;
	Animation* curAnim;
};
