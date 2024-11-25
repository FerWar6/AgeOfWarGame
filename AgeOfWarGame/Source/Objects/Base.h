#pragma once
#include "Objects/Object.h"
#include <cmath>
#include <limits>

class DataManager;

class Base : public Object {
public:
    Base(sf::FloatRect rect, int health, bool enemy);
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    void Damage(int damage);
    int GetHealth();
    void SetHealth(int health);
    void AddHealth(int health);
    bool isEnemy;
    sf::Vector2f frontOfBasePos;
private:
    sf::Texture baseTexture;
    sf::Sprite baseSprite;

    int baseHealth;
    int maxBaseHealth;
};