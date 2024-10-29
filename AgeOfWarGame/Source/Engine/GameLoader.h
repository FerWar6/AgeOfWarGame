#pragma once
#include "Engine/engine.h"
#include "Objects/Base.h"
class GameLoader
{
public:
	GameLoader(DataManager* dataMan);
	void LoadGame(Difficulty difficulty);
	void CreateBase(sf::Vector2f pos, int health, bool enemy);
private:
	DataManager* dataManRef;
};
