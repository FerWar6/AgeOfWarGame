#pragma once
#include "Engine/engine.h"
#include "Data/DataManager.h"
#include "Objects/Object.h"
#include "Objects/Base.h"
#include <cmath>
#include <limits>

class Unit : public Object{
public:
    //Unit Constructor
    Unit(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        bool enemy, float melCooldown, int melDamage, float melSightRange,
        float rangCooldown, int rangDamage, float rangSightRange,
        float alSightRange, int maxHealth, float moveSpeed, float spwnTime,
        int money, int exp);
    Unit(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        bool enemy, float melCooldown, int melDamage, float melSightRange,
        float alSightRange, int maxHealth, float moveSpeed, float spwnTime,
        int money, int exp);
    //Object Overrides
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    //Unit Attack
    void AttackWithCooldown();
    void Attack();
    bool AllyInFront();
    bool OpponentInFront();
    bool OpponentInRange();
    bool ReachedOpponentBase();
    Unit* FindClosestOpponent();
    //Unit Movement
    void MoveUnit();
    //Unit Deletion
    void Damage(int damage);
    void DeleteCheck();
    void DeleteUnit();

    float CalculateDistance(float x1, float x2);

    bool isEnemy;
private:

    sf::Clock meleeAttackCooldownClock;
    float meleeAttackCoolDown;
    int meleeDamage;
    float meleeSightRange;

    bool isRanged;
    sf::Clock rangedAttackCooldownClock;
    float rangedAttackCoolDown;
    int rangedDamage;
    float rangedSightRange;

    float allySightRange;

    int unitMaxHealth;
    int unitHealth;

    float movementSpeed;

    float spawnTime;

    int moneyValue;
    int expValue;

    bool markedForDeletion;
    sf::Clock deletionClock;
    float timeBeforeDeath = 0.05f;
};