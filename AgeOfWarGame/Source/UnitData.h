#pragma once
#include "engine.h"

struct UnitData {
    int maxHealth;
    float movementSpeed;
    int meleeDamage;
    float meleeAttackSpeed;
    int rangedDamage;
    float rangedAttackSpeed;
    float sightRange;
    float spawnTime;
    int expValue;
    int moneyValue;
    std::string textureFile;
};