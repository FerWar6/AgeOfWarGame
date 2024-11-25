#include "Animation.h"
#include "Engine/EngineExtentions/Debug.h"
#include "Management/TextureManagement.h"
#include "Animator.h"
Animation::Animation(sf::String name, sf::Texture& txr, sf::Vector2i frSize, bool loop, std::function<void()> onEnd)
	: currentFrame(1),
	name(name),
	frameSize(frSize),
	fullTexture(txr),
	loopAnimation(loop),
	OnAnimationEnd(onEnd)
{
	amountOfFrames = fullTexture.getSize().x / frameSize.x;
}

Animation::Animation(sf::String name, int animId, SpriteSheet & sheet, bool loop, std::function<void()> onEnd)
	: currentFrame(1),
	name(name),
	frameSize(sheet.GetFrameSize()),
	fullTexture(sheet.GetTexture()),
	amountOfFrames(sheet.GetNumOfFramesInAnim(animId)),
	posOnSheet(0, frameSize.y* (animId - 1)),
	loopAnimation(loop),
	OnAnimationEnd(onEnd)
{
	if (!OnAnimationEnd) {
		//DebugLn("On animation end function missing from: " << GetName());
	}
}

sf::IntRect Animation::GetAnimationFrame()
{
	sf::IntRect rect = sf::IntRect((currentFrame - 1) * frameSize.x, posOnSheet.y, frameSize.x, frameSize.y);
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

void Animation::OnAnimEnd()
{
	if (OnAnimationEnd) {
		OnAnimationEnd();
	}
}

std::string Animation::GetName()
{
	return name;
}

void Animation::UpdateFrame()
{
	if(loopAnimation) currentFrame = (currentFrame % amountOfFrames) + 1;
	else {
		if (currentFrame < amountOfFrames) {
			currentFrame++;
		}
		if (currentFrame == amountOfFrames && !onLastFrame) onLastFrame = true;
		if (currentFrame == amountOfFrames && onLastFrame) OnAnimEnd();
	}
}
