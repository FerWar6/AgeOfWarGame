#pragma once

#include <SFML/Graphics.hpp>

class DataManager;

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


