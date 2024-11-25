#pragma once

#include "Objects/Object.h"
#include "Animation/Animator.h"

class DataManager;
class SpriteSheet;

class Unit : public Object{
public:
    //Unit Constructor
    Unit(sf::FloatRect rect, SpriteSheet& sheet,
        float alSightRange, int maxHealth, float spwnTime);
    Unit(sf::FloatRect rect, SpriteSheet& sheet,
        float alSightRange, int maxHealth, int money, int exp);

    void StartUnit();
    //Object Overrides
    void UpdateObj() override;
    virtual void UnitBehaviour();

    void RenderObj(sf::RenderWindow& win) override;

    //Unit Movement
    //Unit Deletion
    void Damage(int damage);


    float GetTrainTime();

    float CalculateDistance(float x1, float x2);

    bool isEnemy;
    bool GetUnitStopped();
protected:
    bool AllyInFront();
    bool OpponentInFront();
    bool OpponentInRange(float sightRange);
    Unit* FindClosestOpponent();
    bool ReachedOpponentBase(int sightRange);

    void MoveUnit();

    bool stopUnit;
    Animator unitAnim;
    void DeleteCheck();
private:
    SpriteSheet& unitSpriteSheet;
    sf::Sprite unitSprite;
    int t = 0;

    float allySightRange;

    int unitMaxHealth;
    int unitHealth;

    float movementSpeed = 2;

    float spawnTime;

    int moneyValue;
    int expValue;

    sf::Clock deletionClock;
    bool markedForDeletion = false;
    float timeBeforeDeath = 0.05f;
    void DeleteUnit();
};