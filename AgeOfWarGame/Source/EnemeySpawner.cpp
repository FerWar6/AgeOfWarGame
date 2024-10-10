#include "EnemeySpawner.h"

EnemySpawner::EnemySpawner(float cooldown, DataManager* dataMan)
	: Object(sf::Vector2f(0,0), dataMan),
	spawnCooldown(cooldown)
{}
void EnemySpawner::UpdateObj()
{
    if (spawnCooldownClock.getElapsedTime().asSeconds() >= spawnCooldown) {
        dataManRef->CreateEnemy(sf::Vector2f(1200 - 150, 250), dataManRef);
        spawnCooldownClock.restart();
    }
}