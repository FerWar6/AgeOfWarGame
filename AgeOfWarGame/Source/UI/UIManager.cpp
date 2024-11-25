#include "UI/UIManager.h"
#include "Data/DataManager.h"
#include "Objects/Base.h"
#include "Objects/Units/Unit.h"
#include "Engine/GameLoader.h"
#include "Management/TroopManagement.h"
#include "UI/UIRenderer.h"
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

void UIManager::MoveToScreen(Screen screen)
{
    dataManRef->SetScreen(screen);
}

void UIManager::OpenShopMenu(ShopState state)
{
    dataManRef->uiRenRef->SetShopState(state);
}
