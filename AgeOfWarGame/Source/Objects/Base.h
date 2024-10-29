#pragma once
#include "engine/engine.h"
#include "Objects/Object.h"
#include <cmath>
#include <limits>

class DataManager;

class Base : public Object {
public:
    Base(sf::Vector2f pos, DataManager* man, sf::Texture texture, int health, bool enemy);
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    void Damage(int damage);
    bool isEnemy;
    int baseHealth;
    sf::Vector2f frontOfBasePos;
private:
    int maxBaseHealth;
};