#include "UI/UIManager.h"
#include "Objects/Base.h"
#include "Objects/Unit.h"
#include "Engine/GameLoader.h"
#include "Management/TroopManagement.h"
UIManager::UIManager(DataManager* dataMan)
    : dataManRef(dataMan)
{}
void UIManager::SpawnTroop(Age age, UnitType type)
{
    dataManRef->troopManRef->SpawnTroop(age, type);
}
void UIManager::StartGame(Difficulty diff)
{
    dataManRef->gameLdrRef->LoadGame(diff);
}

void UIManager::MoveToScreen(GameScreen screen)
{
    dataManRef->SetGameScreen(screen);
}
