#include "EnemeySpawner.h"
#include "Base.h"

EnemySpawner::EnemySpawner(float cooldown, DataManager* dataMan)
	: spawnCooldown(cooldown),
    dataManRef(dataMan)
{

}
void EnemySpawner::UpdateSpawner()
{
    if (spawnCooldownClock.getElapsedTime().asSeconds() >= spawnCooldown) {
        dataManRef->CreateEnemy(dataManRef->enemyBase->frontOfBasePos, dataManRef, dataManRef->placeHoldTexture);
        spawnCooldownClock.restart();
    }
}