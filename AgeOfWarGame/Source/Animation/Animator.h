#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"
#include "Textures/SpriteSheet.h"
class Animator
{
public:
	Animator(sf::Sprite& sprite);
	void UpdateAnim();
	void SetAnimation(sf::String animName);
	void AddAnimation(sf::String name, sf::Texture& txr, sf::Vector2i frSize,
		bool loop = true, std::function<void()> onEnd = nullptr);
	void AddAnimation(sf::String name, int animId, SpriteSheet& sheet,
		bool loop = true, std::function<void()> onEnd= nullptr);
	Animation& GetAnimation(std::string name);
	std::vector<Animation>& GetAnimations();
private:
	void SetFirstAnim();
	sf::Sprite& sprite;
	std::vector<Animation> animations;
	Animation* curAnim;
};
