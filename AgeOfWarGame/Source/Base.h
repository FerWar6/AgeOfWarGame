#pragma once
#include "Object.h"
#include "engine.h"
#include <cmath>
#include <limits>

class DataManager;

class Base : public Object {
public:
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    Base(sf::Vector2f pos, DataManager* man, sf::Texture texture, int health, bool enemy);
    void Damage(int damage);
    void EndGame(int won);
    bool isEnemy;
    sf::Vector2f frontOfBasePos;
private:
    int baseHealth;
    int maxBaseHealth;
};