#include "Animator.h"

Animator::Animator(sf::Sprite& srt)
	: sprite(srt),
	curAnim(nullptr)
{}

void Animator::UpdateAnim()
{
	sprite.setTexture(curAnim->GetTexture());
	sprite.setTextureRect(curAnim->GetAnimationFrame());
}

void Animator::SetAnimation(sf::String animName)
{
	for (auto& anim : animations) {
		if (anim.GetName() == animName) {
			curAnim = &anim;
			return;
		}
	}
}

void Animator::AddAnimation(sf::String path, sf::String animName)
{
	animations.emplace_back(path, animName);

	if (sprite.getTexture() == nullptr) SetFirstAnim();
}

std::vector<Animation>& Animator::GetAnimations()
{
	return animations;
}

void Animator::SetFirstAnim()
{
	curAnim = &animations[0];
	sprite.setTexture(curAnim->GetTexture());
	sf::IntRect rect = sf::IntRect(0, 0, curAnim->GetFrameSize().x, curAnim->GetFrameSize().y);
	sprite.setTextureRect(rect);
}