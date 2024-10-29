#pragma once
#include "engine/engine.h"
#include "Data/DataManager.h"
class UIManager
{
public:
	UIManager(DataManager* dataMan);
	void SpawnTroop();
	void StartGame();
private:
	DataManager* dataManRef;
};
