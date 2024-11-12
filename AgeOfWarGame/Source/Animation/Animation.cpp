#include "Animation.h"
#include "Engine/EngineExtentions/Debug.h"
#include "Management/TextureManagement.h"
#include "Animator.h"
Animation::Animation(sf::String path)
	: numberOfFrames(TextureManagement::GetAmountOfFrames(path)),
	frameSize(TextureManagement::GetFrameSizeFromName(path)),
	currentFrame(1)
{
	std::cout << "Initializing animation with path: " << path.toAnsiString() << std::endl;
	TextureManagement::LoadTextFromPath(fullTexture, path);
}

sf::IntRect Animation::GetAnimationFrame()
{
	DebugLn(currentFrame);
	sf::IntRect rect = sf::IntRect((currentFrame - 1) * frameSize.x, 0, frameSize.x, frameSize.y);
	UpdateFrame();
	return rect;
}

sf::Texture& Animation::GetTexture()
{
	return fullTexture;
}

void Animation::ResetAnimation()
{
	currentFrame = 1;
}

void Animation::UpdateFrame()
{
	currentFrame = (currentFrame % numberOfFrames) + 1;
}
