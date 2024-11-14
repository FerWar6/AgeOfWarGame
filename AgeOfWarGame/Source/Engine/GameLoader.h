#pragma once

#include "Enums/Difficulty.h"
#include <SFML/Graphics.hpp>

class DataManager;

class GameLoader
{
public:
	GameLoader(DataManager* dataMan);
	void LoadGame(Difficulty difficulty);
	void CreateBase(sf::Vector2f pos, int health, bool enemy);
private:
	DataManager* dataManRef;
};
