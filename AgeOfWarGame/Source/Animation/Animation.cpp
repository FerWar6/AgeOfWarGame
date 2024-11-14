#include "Animation.h"
#include "Engine/EngineExtentions/Debug.h"
#include "Management/TextureManagement.h"
#include "Animator.h"
Animation::Animation(sf::String path, sf::String name)
	: currentFrame(1),
	name(name)
{
	TextureManagement::LoadTextFromPath(fullTexture, path);
	frameSize = TextureManagement::GetFrameSize(path);

	sf::Vector2u textureSize = fullTexture.getSize();
	amountOfFrames = textureSize.x / frameSize.x;
}

sf::IntRect Animation::GetAnimationFrame()
{
	sf::IntRect rect = sf::IntRect((currentFrame - 1) * frameSize.x, 0, frameSize.x, frameSize.y);
	UpdateFrame();
	return rect;
}

sf::Texture& Animation::GetTexture()
{
	return fullTexture;
}

sf::Vector2i Animation::GetFrameSize()
{
	return frameSize;
}

void Animation::ResetAnimation()
{
	currentFrame = 1;
}

sf::String Animation::GetName()
{
	return name;
}

void Animation::UpdateFrame()
{
	currentFrame = (currentFrame % amountOfFrames) + 1;
}
