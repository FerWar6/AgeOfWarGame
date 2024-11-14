#pragma once

#include "Enums/GameScreen.h"
#include "Enums/Difficulty.h"
#include "Enums/UnitType.h"
#include "Enums/Age.h"

class DataManager;

class UIManager
{
public:
	UIManager(DataManager* dataMan);
	void SpawnTroop(Age age, UnitType type);
	void StartGame(Difficulty diff);
	void MoveToScreen(GameScreen screen);
private:
	DataManager* dataManRef;
};
