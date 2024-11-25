#pragma once
#include "Objects/Units/Unit.h"
class RangedUnit : public Unit
{
public:
    RangedUnit(sf::FloatRect rect, SpriteSheet& sheet,
        float melCooldown, int melDamage, float melSightRange,
        float rangCooldown, int rangDamage, float rangRange,
        float alSightRange, int maxHealth, float spwnTime);
    RangedUnit(sf::FloatRect rect, SpriteSheet& sheet,
        float melCooldown, int melDamage, float melSightRange,
        float rangCooldown, int rangDamage, float rangRange,
        float alSightRange, int maxHealth,
        int money, int exp);

    void UnitBehaviour() override;
private:
    void Attack();
    void AttackWithCooldown();

    sf::Clock meleeCooldownClock;
    float meleeCooldown;
    int meleeDamage;
    float meleeRange;

    sf::Clock rangedCooldownClock;
    float rangedCooldown;
    int rangedDamage;
    float rangedRange;
};
