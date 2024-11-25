#include "Unit.h"

#include "Engine/EngineExtentions/Debug.h"

#include "Management/TroopManagement.h"
#include "Management/TextureManagement.h"
#include "Textures/SpriteSheet.h"
#include "Data/DataManager.h"
#include "Objects/Base.h"
#include "UI/UIRenderer.h"

//spawns a guardian unit
Unit::Unit(sf::FloatRect rect, SpriteSheet& sheet,
    float alSightRange, int maxHealth, float spwnTime)
    : Object(rect, true),
    isEnemy(false),
    allySightRange(alSightRange),
    unitMaxHealth(maxHealth),
    unitHealth(maxHealth),
    spawnTime(spwnTime),
    moneyValue(0),
    expValue(0),
    unitSpriteSheet(sheet),
    unitAnim(unitSprite),
    stopUnit(false)
{
    StartUnit();
}
//spawns an enemy unit
Unit::Unit(sf::FloatRect rect, SpriteSheet& sheet,
    float alSightRange, int maxHealth, int money, int exp)
    : Object(rect, true),
    isEnemy(true),
    allySightRange(alSightRange),
    unitMaxHealth(maxHealth),
    unitHealth(maxHealth),
    spawnTime(0),
    moneyValue(money),
    expValue(exp),
    unitSpriteSheet(sheet),
    unitAnim(unitSprite),
    stopUnit(false)
{
    StartUnit();
}

void Unit::StartUnit()
{
    if (isEnemy) {
        unitSprite.setScale(-2.f, 2.f);
        movementSpeed = -movementSpeed;
    }
    else {
        unitSprite.setScale(2, 2);
    }
    if (unitSpriteSheet.GetAmountOfAnimations() == 4) {
        unitAnim.AddAnimation("run", 1, unitSpriteSheet);
        unitAnim.AddAnimation("idle", 2, unitSpriteSheet);
        unitAnim.AddAnimation("attack", 3, unitSpriteSheet);
        unitAnim.AddAnimation("die", 4, unitSpriteSheet, false, std::bind(&Unit::DeleteUnit, this));
    }
    if (unitSpriteSheet.GetAmountOfAnimations() == 5) {
        unitAnim.AddAnimation("run", 1, unitSpriteSheet);
        unitAnim.AddAnimation("idle", 2, unitSpriteSheet);
        unitAnim.AddAnimation("attack", 3, unitSpriteSheet);
        unitAnim.AddAnimation("die", 4, unitSpriteSheet, false, std::bind(&Unit::DeleteUnit, this));
        unitAnim.AddAnimation("rangedAttack", 5, unitSpriteSheet);
    }
    t = 5;
}


void Unit::UpdateObj()
{
    UnitBehaviour();
}
void Unit::RenderObj(sf::RenderWindow& win) {
    //update the animation at 5 
    //each frame in attack animation adds 0.2 seconds to the cooldown
    if (unitAnim.GetAnimations().size() > 0) {
        if (t >= 5) {
            unitAnim.UpdateAnim();
            t = 1;
        }
        else {
            t++;
        }

        sf::FloatRect unitBounds = unitSprite.getLocalBounds();
        unitSprite.setOrigin(unitBounds.width / 2, unitBounds.height);
        unitSprite.setPosition(GetPos());
        win.draw(unitSprite);
    }
    else {
        sf::Vector2f UnitSize(25, 50);
        sf::Vector2f centerPos = sf::Vector2f(GetPos().x - UnitSize.x / 2, GetPos().y - UnitSize.y / 2);
        sf::RectangleShape unitShape(UnitSize);
        unitShape.setPosition(centerPos);
        sf::Color col = isEnemy ? col = sf::Color::Red : sf::Color::Green;
        unitShape.setFillColor(col);
        win.draw(unitShape);
    }
    if (!markedForDeletion && !stopUnit) {
        sf::Vector2f barSize(30, 7);
        sf::FloatRect unitBounds = unitSprite.getLocalBounds();
        float percentage = static_cast<float>(unitHealth) / static_cast<float>(unitMaxHealth);
        dataManRef->uiRenRef->DrawBar(barSize, sf::Vector2f(GetPos().x, GetPos().y - unitBounds.height - 20), percentage, sf::Color::Red);
    }
}
void Unit::UnitBehaviour() {}
//----------------------------------Unit Behaviour------------------------------------------
void Unit::MoveUnit() {
    sf::Vector2f newPos = GetPos();
    newPos.x += movementSpeed;
    SetPos(newPos);
}
bool Unit::AllyInFront() {
    std::vector<Unit*> allyList = isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& unit : allyList) {
        //if ally is in front of this unit, return true
        if (isEnemy) {
            if (unit->GetPos().x < this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, unit->GetPos().x) <= allySightRange) return true;
            }
        }
        else {
            if (unit->GetPos().x > this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, unit->GetPos().x) <= allySightRange) return true;
            }
        }
    }
    return false;
}

bool Unit::OpponentInFront()
{
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& opp : opponentList) {
        if (isEnemy) {
            if (opp->GetPos().x < this->GetPos().x) return true;
        }
        else {
            if (opp->GetPos().x > this->GetPos().x) return true;
        }
    }
    return false;
}

bool Unit::OpponentInRange(float sightRange) {
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& opp : opponentList) {
        float distance = CalculateDistance(this->GetPos().x, opp->GetPos().x);
        if (distance <= sightRange) {
            return true;
        }
    }
    return false;
}
Unit* Unit::FindClosestOpponent() {
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    Unit* closestOpp = nullptr;
    float closestDistance = 9999;

    for (Unit* opp : opponentList) {
        float distance = CalculateDistance(this->GetPos().x, opp->GetPos().x);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestOpp = opp;
        }
    }
    return closestOpp;
}
bool Unit::ReachedOpponentBase(int sightRange)
{
    Base* targetBase = isEnemy ? dataManRef->playerBase : dataManRef->enemyBase;

    float distance = CalculateDistance(this->GetPos().x, targetBase->GetPos().x);
    if (distance <= sightRange) {
        return true;
    }
    return false;
}

float Unit::GetTrainTime()
{
    return spawnTime;
}

float Unit::CalculateDistance(float x1, float x2) {
    return std::abs(x1 - x2);
}
bool Unit::GetUnitStopped()
{
    return stopUnit;
}
void Unit::Damage(int damage) {
    unitHealth -= damage;
    //std::cout << "Damaged Unit, Health is now: " << unitHealth << std::endl;
    if (unitHealth <= 0) {
        //std::cout << "Marked for deletion" << std::endl;
        markedForDeletion = true;
    }
}
void Unit::DeleteCheck() {
    if (markedForDeletion) {
        if (deletionClock.getElapsedTime().asSeconds() >= timeBeforeDeath) {
            stopUnit = true;
            unitAnim.SetAnimation("die");
            if (isEnemy) {
                dataManRef->AddPlayerMoney(moneyValue);
                dataManRef->AddPlayerExperience(expValue);
            }
            //the animator will call deleteunit when the animation is over
        }
    }
    else if(!markedForDeletion){
        deletionClock.restart();
    }
}
void Unit::DeleteUnit() {
    dataManRef->MarkObjForDel(this);
}