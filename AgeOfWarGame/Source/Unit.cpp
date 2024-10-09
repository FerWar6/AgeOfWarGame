#include "Unit.h"

Unit::Unit(bool enemy, sf::Vector2f pos, DataManager* man, int maxHealth = 100, float speed = 1.0f,
    int meleeDmg = 10, float meleeAtckSpd = 1.0f,
    int rangedDmg = 15, float rangedAtckSpd = 1.0f,
    float sightRnge = 100.0f, float spwnTime = 1.0f,
    int exp = 0, int money = 0)
    : Object(pos, man),
    isEnemy(enemy),
    unitMaxHealth(maxHealth),
    movementSpeed(speed),
    meleeDamage(meleeDmg),
    meleeAttackCoolDown(meleeAtckSpd),
    rangedDamage(rangedDmg),
    rangedAttackCoolDown(rangedAtckSpd),
    sightRange(sightRnge),
    spawnTime(spwnTime),
    expValue(exp),
    moneyValue(money)
{
    unitHealth = maxHealth;
    if (isEnemy) movementSpeed = -movementSpeed;
    markedForDeletion = false;
    waitForAllyRange = 100;
}
void Unit::UpdateObj()
{
    if (OpponentInRange()) {
        AttackWithCooldown();
    }
    else if (!OpponentInRange() && !AllyInFront()) {
        MoveUnit();
        attackCooldownClock.restart();
    }
    DeleteCheck();
}
void Unit::RenderObj(sf::RenderWindow& win) {
    sf::Vector2f UnitSize(25, 50);
    sf::Vector2f centerPos = sf::Vector2f(GetPos().x - UnitSize.x / 2, GetPos().y - UnitSize.y / 2);
    sf::RectangleShape unitShape(UnitSize);
    unitShape.setPosition(centerPos);
    sf::Color col = isEnemy ? col = sf::Color::Red : sf::Color::Green;
    unitShape.setFillColor(col);
    win.draw(unitShape);
    if (!markedForDeletion) {
        sf::Vector2f barSize(30, 7);
        float percentage = static_cast<float>(unitHealth) / static_cast<float>(unitMaxHealth);
        bar.Draw(barSize, sf::Vector2f(GetPos().x, GetPos().y - 50), percentage, win);
    }
}
//----------------------------------Enemy Behaviour------------------------------------------
bool Unit::AllyInFront() {
    std::vector<Unit*> allyList = isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& unit : allyList) {
        //if ally is in front of this unit, return true
        if (isEnemy) {
            if (unit->GetPos().x < this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, unit->GetPos().x) <= waitForAllyRange) return true;
            }
        }
        else {
            if (unit->GetPos().x > this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, unit->GetPos().x) <= waitForAllyRange) return true;
            }
        }
    }
    return false;
}

bool Unit::OpponentInFront()
{
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();
    for (const auto& opp : opponentList) {
        if (!isEnemy) {
            if (opp->GetPos().x < this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, opp->GetPos().x) <= waitForAllyRange) return true;
            }
        }
        else {
            if (opp->GetPos().x > this->GetPos().x) {
                if (CalculateDistance(this->GetPos().x, opp->GetPos().x) <= waitForAllyRange) return true;
            }
        }
    }
    return false;
}

bool Unit::OpponentInRange() {
    std::vector<Unit*> unitList;
    isEnemy ? unitList = dataManRef->GetGuardians() : unitList = dataManRef->GetEnemies();
    for (const auto& unit : unitList) {
        float distance = CalculateDistance(this->GetPos(), unit->GetPos());
        if (distance <= sightRange) {
            return true;
        }
    }
    if (isEnemy) {
        float distance = CalculateDistance(this->GetPos(), dataManRef->playerBase->GetPos());
        if (distance <= sightRange) return true;
    }
    if (!isEnemy) {
        float distance = CalculateDistance(this->GetPos(), dataManRef->enemyBase->GetPos());
        if (distance <= sightRange) return true;
    }
    
    return false;
}


Unit* Unit::FindClosestOpponent() {
    std::vector<Unit*> opponentList = !isEnemy ? dataManRef->GetEnemies() : dataManRef->GetGuardians();

    std::vector<Unit*> unitList;
    isEnemy ? unitList = dataManRef->GetGuardians() : unitList = dataManRef->GetEnemies();
    Unit* closestUnit = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (Unit* unit : unitList) {
        float distance = CalculateDistance(this->GetPos(), unit->GetPos());

        if (distance < closestDistance) {
            closestDistance = distance;
            closestUnit = unit;
        }
    }
    return closestUnit;
}
void Unit::Attack() {
    Unit* closestUnit = FindClosestUnit();
    //std::cout << "Attack" << std::endl;
    if (isEnemy) {
        float distance = CalculateDistance(this->GetPos(), dataManRef->playerBase->GetPos());
        if (distance < closestUnit->GetPos().x) {
            dataManRef->playerBase->Damage(10);
        }
        else {
            dataManRef->DamageUnit(closestUnit, 25);
        }
    }
    if (!isEnemy) {
        float distance = CalculateDistance(this->GetPos(), dataManRef->enemyBase->GetPos());
        if (distance < closestUnit->GetPos().x) {
            dataManRef->enemyBase->Damage(10);
        }
        else {
            dataManRef->DamageUnit(closestUnit, 25);
        }
    }
}
void Unit::AttackWithCooldown() {
    if (attackCooldownClock.getElapsedTime().asSeconds() >= meleeAttackCoolDown) {
        Attack();
        attackCooldownClock.restart();
    }   
}
void Unit::Damage(int damage) {
    unitHealth -= damage;
    //std::cout << "Damaged Unit, Health is now: " << unitHealth << std::endl;
    if (unitHealth <= 0) {
        //std::cout << "Marked for deletion" << std::endl;
        markedForDeletion = true;
    }
}

void Unit::MoveUnit() {
    sf::Vector2f newPos = GetPos();
    newPos.x += movementSpeed / 10;
    SetPos(newPos);
}
float CalculateDistance(float x1, float x2) {
    return std::abs(x1 - x2);
}
//float CalculateDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
//    float dx = pos1.x - pos2.x;
//    float dy = pos1.y - pos2.y;
//    return std::sqrt(dx * dx + dy * dy);
//}
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
    //std::cout << "delete" << std::endl;
    dataManRef->DeleteUnit(this);
}