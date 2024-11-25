#include "Base.h"

#include "Data/DataManager.h"
#include "UI/UIRenderer.h"
#include "Textures/TextureLoader.h"
Base::Base(sf::FloatRect rect, int health, bool enemy)
	: Object(rect),
	maxBaseHealth(health),
	isEnemy(enemy)
{
    int frontOfBaseMargin = 70;
    frontOfBasePos = sf::Vector2f(isEnemy ? GetPos().x - frontOfBaseMargin : GetPos().x + frontOfBaseMargin, dataManRef->groundPos);
    baseHealth = maxBaseHealth;
    baseTexture = dataManRef->textureLdrRef->GetTexture("basePlaceholder");
    baseSprite.setTexture(baseTexture);
}
void Base::UpdateObj()
{
}

void Base::RenderObj(sf::RenderWindow& win)
{
    sf::Vector2u baseSize = baseTexture.getSize();
    sf::Vector2 basePos = sf::Vector2(GetPos().x - baseSize.x/2, GetPos().y - baseSize.y);
    baseSprite.setPosition(basePos);
    win.draw(baseSprite);
    //sf::RectangleShape unitShape(baseSize);
    //sf::Vector2 basePos = sf::Vector2(GetPos().x - baseSize.x/2, GetPos().y - baseSize.y);
    ////basePos.x += (isEnemy ? -baseSize.x : 0);
    //unitShape.setPosition(basePos);
    //sf::Color col = isEnemy ? col = sf::Color::Red : sf::Color::Green;
    //unitShape.setFillColor(col);
    //win.draw(unitShape);

    sf::Vector2f barSize(100, 10);
    float percentage = static_cast<float>(baseHealth) / static_cast<float>(maxBaseHealth);
    dataManRef->uiRenRef->DrawBar(barSize, sf::Vector2f(GetPos().x, GetPos().y - baseSize.y - 10), percentage, sf::Color::Red);
}
void Base::Damage(int damage)
{
    dataManRef->DamageBase(this, damage);
}

int Base::GetHealth()
{
    return baseHealth;
}

void Base::SetHealth(int health)
{
    maxBaseHealth = health;
    baseHealth = health;
}

void Base::AddHealth(int health)
{
    baseHealth += health;
}
