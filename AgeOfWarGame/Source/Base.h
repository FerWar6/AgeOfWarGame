#pragma once
#include "Object.h"
#include "engine.h"
#include "DataManager.h"
#include <cmath>
#include <limits>

//class DataManager;

class Base : public Object {
public:
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    Base(sf::Vector2f pos, DataManager* man, int health, bool enemy);
    void Damage(int damage);
    void EndGame();
    bool isEnemy;
private:
    int baseHealth;
    int maxBaseHealth;
    HealthBar bar;
};