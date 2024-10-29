#include "UI/UIManager.h"
#include "Objects/Base.h"

UIManager::UIManager(DataManager* dataMan)
    : dataManRef(dataMan)
{}

void UIManager::SpawnTroop()
{
    int unitCost = 25;
    if (dataManRef->playerMoney >= unitCost) {
        dataManRef->CreateGuardian(dataManRef->playerBase->frontOfBasePos, dataManRef, dataManRef->placeHoldTexture);
        dataManRef->playerMoney -= unitCost;
    }
}

void UIManager::StartGame()
{
    dataManRef->SetGameState(GameState::GameScreen);
}
