#include "Animator.h"

Animator::Animator(sf::Sprite& srt)
	: sprite(srt)
{}

void Animator::UpdateAnim()
{
	int animationIndex = 0;
	sprite.setTexture(animations[animationIndex].GetTexture());
	sprite.setTextureRect(animations[animationIndex].GetAnimationFrame());
}

void Animator::AddAnimation(sf::String path)
{
	animations.emplace_back(path);
	if (sprite.getTexture() == nullptr) {
		sprite.setTexture(animations[0].GetTexture());
		sprite.setTextureRect(animations[0].GetAnimationFrame());
	}
}

std::vector<Animation>& Animator::GetAnimations()
{
	return animations;
}


