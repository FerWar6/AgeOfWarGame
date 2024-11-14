#include "Base.h"

#include "Data/DataManager.h"
#include "UI/UIRenderer.h"

Base::Base(sf::Vector2f pos, DataManager* man, sf::Texture texture, int health, bool enemy)
	: Object(pos, man),
	maxBaseHealth(health),
	isEnemy(enemy)
{
    frontOfBasePos = sf::Vector2f(isEnemy ? pos.x - 70 : pos.x + 70, pos.y);
    baseHealth = maxBaseHealth;
}
void Base::UpdateObj()
{
}

void Base::RenderObj(sf::RenderWindow& win)
{
    sf::Vector2f baseSize(100, 200);
    sf::RectangleShape unitShape(baseSize);
    sf::Vector2 basePos = sf::Vector2(GetPos().x - baseSize.x/2, GetPos().y - baseSize.y / 2);
    //basePos.x += (isEnemy ? -baseSize.x : 0);
    unitShape.setPosition(basePos);
    sf::Color col = isEnemy ? col = sf::Color::Red : sf::Color::Green;
    unitShape.setFillColor(col);
    win.draw(unitShape);

    sf::Vector2f barSize(75, 10);
    float percentage = static_cast<float>(baseHealth) / static_cast<float>(maxBaseHealth);
    dataManRef->uiRenRef->DrawBar(barSize, sf::Vector2f(GetPos().x, GetPos().y - 120), percentage, sf::Color::Red);
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
