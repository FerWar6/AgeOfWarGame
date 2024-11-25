#pragma once

#include "Objects/Units/Unit.h"
class MeleeUnit : public Unit
{
public:
    MeleeUnit(sf::FloatRect rect, SpriteSheet& sheet,
        float melCooldown, int melDamage, float melSightRange,
        float alSightRange, int maxHealth, float spwnTime);
    MeleeUnit(sf::FloatRect rect, SpriteSheet& sheet,
        float melCooldown, int melDamage, float melSightRange,
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
};

