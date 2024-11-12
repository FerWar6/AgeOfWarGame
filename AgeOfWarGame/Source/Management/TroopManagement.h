#pragma once

#include "Engine/engine.h"
#include "Data/DataManager.h"
class TroopManagement
{
public:
	TroopManagement(DataManager* dataMan);
	void SpawnTroop(Age age, UnitType type);
	void SpawnEnemyTroop(Age age, UnitType type);
private:
	DataManager* dataManRef;
};
