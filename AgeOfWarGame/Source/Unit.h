#pragma once
#include "HealthBar.h"
#include "Object.h"
#include "engine.h"
#include "Base.h"
#include "DataManager.h"
#include <cmath>
#include <limits>
//class DataManager;

class Unit : public Object{
public:
    void UpdateObj() override;
    void RenderObj(sf::RenderWindow& win) override;
    Unit(bool enemy, sf::Vector2f pos, DataManager* man, int health, float speed, int meleeDmg, float meleeAtckSpd,
        int rangedDmg, float rangedAtckSpd, float sightRnge, float spwnTime,
        int exp, int money);
    void AttackWithCooldown();
    void DeleteCheck();
    void DeleteUnit();
    bool OpponentInRange();
    bool AllyInFront();
    bool OpponentInFront();
    Unit* FindClosestOpponent();
    bool ReachedOpponentBase();
    float CalculateDistance(float x1, float x2);
    void Attack();
    void MoveUnit();
    void Damage(int damage);
    bool isEnemy; //Is the unit an enemy

    sf::Clock attackCooldownClock;
    float meleeAttackCoolDown; //Units melee attack speed

private:
    HealthBar bar;

    sf::Clock deletionClock;
    float timeBeforeDeath = 0.05f;

    int unitMaxHealth;
    int unitHealth; //Units health
    float movementSpeed; //Units movement speed

    int meleeDamage; //Units melee attack damage
    int rangedDamage; //Units ranged attack damage
    float rangedAttackCoolDown; //Units ranged attack speed

    float waitForAllyRange;
    float sightRange; //The sight range of the Unit
    //bool opponentInRange; //Is true if the opponent is in range
    float spawnTime; //The time for a Unit to spawn

    int expValue; //The amount of experience the player gains when an enemy Unit is killed
    int moneyValue; //The amount of money the player gains when an enemy Unit is killed

    //float timeInSight;
    bool markedForDeletion;
};