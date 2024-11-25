#pragma once

#include "Enums/Screen.h"
#include "Enums/Difficulty.h"
#include "Enums/UnitType.h"
#include "Enums/Age.h"
#include "Enums/ShopState.h"

class DataManager;

class UIManager
{
public:
	UIManager(DataManager* dataMan);
	void SpawnTroop(Age age, UnitType type);
	void StartGame(Difficulty diff);
	void MoveToScreen(Screen screen);
	void OpenShopMenu(ShopState state);
private:
	DataManager* dataManRef;
};
