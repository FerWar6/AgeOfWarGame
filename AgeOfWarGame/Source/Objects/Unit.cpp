#include "Objects/Unit.h"

Unit::Unit(sf::Vector2f pos, DataManager* man, sf::String path,
    bool enemy, float melCooldown, int melDamage, float melSightRange,
    float rangCooldown, int rangDamage, float rangSightRange,
    float alSightRange, int maxHealth, float moveSpeed, float spwnTime,
    int money, int exp)
    : Object(pos, man, texture),
    isEnemy(enemy),
    meleeAttackCoolDown(melCooldown),
    meleeDamage(melDamage),
    meleeSightRange(melSightRange),
    isRanged(true),
    rangedAttackCoolDown(rangCooldown),
    rangedDamage(rangDamage),
    rangedSightRange(rangSightRange),
    allySightRange(alSightRange),
    unitMaxHealth(maxHealth),
    movementSpeed(moveSpeed),
    spawnTime(spwnTime),
    moneyValue(money),
    expValue(exp),
    timeBeforeDeath(0.05f)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading unit texture!" << std::endl;
    }
    unitSprite.setTexture(texture);
    if(isEnemy) unitSprite.setScale(-1.f, 1.f);


    unitHealth = maxHealth;
    if (isEnemy) movementSpeed = -movementSpeed;
    markedForDeletion = false;
}
void Unit::UpdateObj()
{
    if (OpponentInRange() || ReachedOpponentBase()) {
        AttackWithCooldown();
    }
    else if (!AllyInFront()) {
        MoveUnit();
        meleeAttackCooldownClock.restart();
    }
    else {
        meleeAttackCooldownClock.restart();
    }
    DeleteCheck();
}
void Unit::RenderObj(sf::RenderWindow& win) {
    if (unitSprite.getTexture() != nullptr) {
        sf::FloatRect unitBounds = unitSprite.getLocalBounds();
        unitSprite.setOrigin(unitBounds.width / 2, unitBounds.height / 2);
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
    if (!markedForDeletion) {
        sf::Vector2f barSize(30, 7);
        float percentage = static_cast<float>(unitHealth) / static_cast<float>(unitMaxHealth);
        dataManRef->uiRenRef->DrawBar(barSize, sf::Vector2f(GetPos().x, GetPos().y - 50), percentage, sf::Color::Red);
    }
}
//----------------------------------Enemy Behaviour------------------------------------------
void Unit::MoveUnit() {
    sf::Vector2f newPos = GetPos();
    newPos.x += movementSpeed / 10;
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

bool Unit::OpponentInRange() {
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& opp : opponentList) {
        float distance = CalculateDistance(this->GetPos().x, opp->GetPos().x);
        if (distance <= meleeSightRange) {
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
bool Unit::ReachedOpponentBase()
{
    Base* targetBase = isEnemy ? dataManRef->playerBase : dataManRef->enemyBase;

    float distance = CalculateDistance(this->GetPos().x, targetBase->GetPos().x);
    if (distance <= meleeSightRange) {
        return true;
    }
    return false;
}
void Unit::Attack() {
    //std::cout << "attack!" << OpponentInFront() << OpponentInRange() << std::endl;
    if (OpponentInFront()) {
        Unit* targetUnit = FindClosestOpponent();
        targetUnit->Damage(34);
        //std::cout << "attack opponent" << std::endl;

    }
    else if(ReachedOpponentBase()){
        Base* targetBase = isEnemy ? dataManRef->playerBase : dataManRef->enemyBase;
        targetBase->Damage(10);
        //std::cout << "attack base" << std::endl;
    }
}
void Unit::AttackWithCooldown() {
    if (meleeAttackCooldownClock.getElapsedTime().asSeconds() >= meleeAttackCoolDown) {
        Attack();
        meleeAttackCooldownClock.restart();
    }   
}

float Unit::CalculateDistance(float x1, float x2) {
    return std::abs(x1 - x2);
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
            DeleteUnit();
        }
    }
    else if(!markedForDeletion){
        deletionClock.restart();
    }
}
void Unit::DeleteUnit() {

    if (isEnemy) {
        dataManRef->AddPlayerMoney(moneyValue);
        dataManRef->AddPlayerExperience(expValue);
    }

    dataManRef->MarkObjForDel(this);
}