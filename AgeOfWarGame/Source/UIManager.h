#pragma once
#include "engine.h"
#include "DataManager.h"
#include "UIManager.h"
class UIManager
{
public:
	UIManager(DataManager* dataMan);
	void SpawnTroop();
private:
	DataManager* dataManRef;
};
