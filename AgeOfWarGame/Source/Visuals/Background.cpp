#include "Background.h"
#include "Data/ServiceLocator.h"
#include "Engine/engine.h"
Background::Background(TextureLoader* txrLdr)
	: bgTexture(txrLdr->GetTexture("Background")),
	groundTexture(txrLdr->GetTexture("Ground")),
	posSet(false)
{
	bgTexture.setRepeated(true);
	bgSprite.setTexture(bgTexture);
	groundTexture.setRepeated(true);
	groundSprite.setTexture(groundTexture);
}

void Background::Drawbg(sf::RenderWindow& win)
{
	if (!posSet) {
		sf::Vector2u windowSize = win.getSize();
		sf::FloatRect bounds = bgSprite.getLocalBounds();

		if (windowSize.y > bounds.height) {
			float multiplier = windowSize.y / bounds.height;
			bgSprite.setScale(multiplier, multiplier);

			float widthMultiplier = static_cast<float>(sl::GetDataManager()->engineRef->GetWorldSize()) / bgTexture.getSize().x;
			sf::IntRect bgSpriteRect = sf::IntRect(0, 0, bgTexture.getSize().x * (widthMultiplier + 0.1), bgTexture.getSize().y);
			bgSprite.setTextureRect(bgSpriteRect);
		}
		bounds = bgSprite.getLocalBounds();
		bgSprite.setOrigin(bounds.width/2,bounds.height/2);
		bgSprite.setPosition(windowSize.x / 2, windowSize.y / 2);

		bounds = groundSprite.getLocalBounds();
		float widthMultiplier = static_cast<float>(sl::GetDataManager()->engineRef->GetWorldSize()) / groundTexture.getSize().x;
		sf::IntRect groundSpriteRect = sf::IntRect(0, 0, groundTexture.getSize().x * (widthMultiplier + 0.1), groundTexture.getSize().y);
		groundSprite.setPosition(0, windowSize.y - groundTexture.getSize().y);
		groundSprite.setTextureRect(groundSpriteRect);
		posSet = true;
	}
	win.draw(bgSprite);
	win.draw(groundSprite);
}

