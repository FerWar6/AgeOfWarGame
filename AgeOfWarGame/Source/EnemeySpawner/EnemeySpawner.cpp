#include "EnemeySpawner/EnemeySpawner.h"
#include "Objects/Base.h"
#include "Objects/Unit.h"
#include "Management/TroopManagement.h"

EnemySpawner::EnemySpawner(float cooldown, DataManager* dataMan)
	: spawnCooldown(cooldown),
    dataManRef(dataMan)
{}
void EnemySpawner::UpdateSpawner()
{
    //if (spawnCooldownClock.getElapsedTime().asSeconds() >= spawnCooldown) {
    //    dataManRef->troopManRef->SpawnEnemyTroop(Age::Arcade, UnitType::Melee);
    //    spawnCooldownClock.restart();
    //}
}