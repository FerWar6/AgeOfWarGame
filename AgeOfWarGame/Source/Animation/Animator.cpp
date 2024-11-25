#include "Animator.h"
#include "Engine/EngineExtentions/Debug.h"

Animator::Animator(sf::Sprite& srt)
	: sprite(srt),
	curAnim(nullptr)
{}

void Animator::UpdateAnim()
{
	if (animations.size() != 0) {
		sprite.setTexture(curAnim->GetTexture());
		sprite.setTextureRect(curAnim->GetAnimationFrame());
	}
	else { DebugLn("Missing Animation In Animator"); }

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

void Animator::AddAnimation(sf::String name, sf::Texture& txr, sf::Vector2i frSize, bool loop, std::function<void()> onEnd)
{
	animations.emplace_back(name, txr, frSize, loop, onEnd);
	if (sprite.getTexture() == nullptr) SetFirstAnim();
}
void Animator::AddAnimation(sf::String name, int animId, SpriteSheet& sheet, bool loop, std::function<void()> onEnd)
{
	animations.emplace_back(name, animId, sheet, loop, onEnd);
	if (sprite.getTexture() == nullptr) SetFirstAnim();
}
Animation& Animator::GetAnimation(std::string name)
{
	for (Animation& anim : GetAnimations()) {
		std::string animName = anim.GetName();
		if (name.compare(animName) == 0) {
			return anim;
		}
	}
	DebugLn("Couldnt find animation: " << name);
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