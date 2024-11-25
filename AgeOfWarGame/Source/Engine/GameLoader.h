#pragma once

#include "Enums/Difficulty.h"
#include <SFML/Graphics.hpp>

class DataManager;

class GameLoader
{
public:
	GameLoader(DataManager* dataMan);
	void CreateBases();
	void LoadGame(Difficulty difficulty);
private:
	void CreateBase(sf::FloatRect rect, int health, bool enemy);
	DataManager* dataManRef;
};
