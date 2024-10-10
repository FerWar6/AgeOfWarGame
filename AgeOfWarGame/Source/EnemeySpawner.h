#include "Object.h"
#include "engine.h"
#pragma once
class EnemySpawner : public Object
{
public:
	EnemySpawner(float cooldown, DataManager* dataMan);
	void UpdateObj() override;
	float spawnCooldown;
private:
	sf::Clock spawnCooldownClock;
};


