#include "EnemeySpawner/EnemeySpawner.h"
#include "Objects/Base.h"
#include "Objects/Unit.h"

EnemySpawner::EnemySpawner(float cooldown, DataManager* dataMan)
	: spawnCooldown(cooldown),
    dataManRef(dataMan)
{}
void EnemySpawner::UpdateSpawner()
{
    if (spawnCooldownClock.getElapsedTime().asSeconds() >= spawnCooldown) {
        sf::String path = "Assets/meleeUnitSprite.png";
        Unit* newEnemy = new Unit(dataManRef->enemyBase->frontOfBasePos, dataManRef, path, true, 0.75, 34,
            100, 0, 0, 0, 75, 100, 1, 1, 50, 50);
        dataManRef->MarkObjForAdd(newEnemy);
        spawnCooldownClock.restart();
    }
}