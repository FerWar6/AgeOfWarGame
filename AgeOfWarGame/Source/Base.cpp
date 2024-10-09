#include "Base.h"

Base::Base(sf::Vector2f pos, DataManager* man, int health, bool enemy)
	: Object(pos, man),
	maxBaseHealth(health),
	isEnemy(enemy)
{
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
    bar.Draw(barSize, sf::Vector2f(GetPos().x, GetPos().y - 120), percentage, win);
}
void Base::Damage(int damage)
{
    baseHealth -= damage;
    if (baseHealth <= 0) EndGame();
}
void Base::EndGame()
{
    isEnemy ? std::cout << "You Won" : std::cout << "You Lost";
}
