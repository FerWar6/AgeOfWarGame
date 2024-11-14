#pragma once

#include "Enums/UnitType.h"
#include "Enums/Age.h"

class DataManager;

class TroopManagement
{
public:
	TroopManagement(DataManager* dataMan);
	void SpawnTroop(Age age, UnitType type);
	void SpawnEnemyTroop(Age age, UnitType type);
private:
	DataManager* dataManRef;
};
