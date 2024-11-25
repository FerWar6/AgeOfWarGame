#include "RangedUnit.h"

#include "Objects/Base.h"
#include "Data/DataManager.h"
#include "Engine/EngineExtentions/Debug.h"
RangedUnit::RangedUnit(sf::FloatRect rect, SpriteSheet& sheet,
	float melCooldown, int melDamage, float melSightRange, 
	float rangCooldown, int rangDamage, float rangRange, 
	float alSightRange, int maxHealth, float spwnTime)
	: Unit(rect, sheet, alSightRange, maxHealth, spwnTime),
	meleeCooldown(melCooldown),
	meleeDamage(melDamage),
	meleeRange(melSightRange),
	rangedCooldown(rangCooldown),
	rangedDamage(rangDamage),
	rangedRange(rangRange)
{
}

RangedUnit::RangedUnit(sf::FloatRect rect, SpriteSheet& sheet,
	float melCooldown, int melDamage, float melSightRange, 
	float rangCooldown, int rangDamage, float rangRange, 
	float alSightRange, int maxHealth, int money, int exp)
	: Unit(rect, sheet, alSightRange, maxHealth, money, exp),
	meleeCooldown(melCooldown),
	meleeDamage(melDamage),
	meleeRange(melSightRange),
	rangedCooldown(rangCooldown),
	rangedDamage(rangDamage),
	rangedRange(rangRange)
{
}

void RangedUnit::UnitBehaviour()
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
			rangedCooldownClock.restart();
		}
		else if (OpponentInRange(rangedRange) || ReachedOpponentBase(rangedRange)) {
			//DebugLn("Ranged Attacking");
			unitAnim.SetAnimation("rangedAttack");
			AttackWithCooldown();
		}
		else {
			unitAnim.SetAnimation("idle");
			meleeCooldownClock.restart();
			rangedCooldownClock.restart();
		}
		DeleteCheck();
	}
}

void RangedUnit::Attack()
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

void RangedUnit::AttackWithCooldown()
{
	if (meleeCooldownClock.getElapsedTime().asSeconds() >= meleeCooldown) {
		Attack();
		meleeCooldownClock.restart();
	}
}
