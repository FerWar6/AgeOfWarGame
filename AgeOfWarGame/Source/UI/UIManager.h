#pragma once
#include "engine/engine.h"
#include "Data/DataManager.h"
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
