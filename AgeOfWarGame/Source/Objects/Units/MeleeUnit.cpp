#include "MeleeUnit.h"

#include "Objects/Base.h"
#include "Data/DataManager.h"
MeleeUnit::MeleeUnit(sf::FloatRect rect, SpriteSheet& sheet,
	float melCooldown, int melDamage, float melSightRange,
	float alSightRange, int maxHealth, float spwnTime)
	: Unit(rect, sheet, alSightRange, maxHealth, spwnTime),
	meleeCooldown(melCooldown),
	meleeDamage(melDamage),
	meleeRange(melSightRange)
{
}

MeleeUnit::MeleeUnit(sf::FloatRect rect, SpriteSheet& sheet,
	float melCooldown, int melDamage, float melSightRange,
	float alSightRange, int maxHealth, int money, int exp)
	: Unit(rect, sheet, alSightRange, maxHealth, money, exp),
	meleeCooldown(melCooldown),
	meleeDamage(melDamage),
	meleeRange(melSightRange)
{
}

void MeleeUnit::UnitBehaviour()
{
    if (!stopUnit) {
        if (OpponentInRange(meleeRange) || ReachedOpponentBase(meleeRange)) {
            unitAnim.SetAnimation("attack");
            AttackWithCooldown();
        }
        else if (!AllyInFront()) {
            MoveUnit();
            unitAnim.SetAnimation("run");
            meleeCooldownClock.restart();
        }
        else {
            unitAnim.SetAnimation("idle");
            meleeCooldownClock.restart();
        }
        DeleteCheck();
    }
}
void MeleeUnit::Attack()
{
    if (OpponentInFront()) {
        Unit* targetUnit = FindClosestOpponent();
        targetUnit->Damage(34);
        //std::cout << "attack opponent" << std::endl;

    }
    else if (ReachedOpponentBase(meleeRange)) {
        Base* targetBase = isEnemy ? dataManRef->playerBase : dataManRef->enemyBase;
        targetBase->Damage(10);
        //std::cout << "attack base" << std::endl;
    }
}
void MeleeUnit::AttackWithCooldown()
{
    if (meleeCooldownClock.getElapsedTime().asSeconds() >= meleeCooldown) {
        Attack();
        meleeCooldownClock.restart();
    }
}
