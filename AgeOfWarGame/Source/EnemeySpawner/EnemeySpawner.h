#pragma once
#include "Data/DataManager.h"
#include "engine/engine.h"
class EnemySpawner{
public:
	EnemySpawner(float cooldown, DataManager* dataMan);
	void UpdateSpawner();
	float spawnCooldown;
private:
	sf::Clock spawnCooldownClock;
	DataManager* dataManRef;
	sf::Texture texture;
};


