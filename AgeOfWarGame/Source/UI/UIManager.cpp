#include "UI/UIManager.h"
#include "Objects/Base.h"
#include "Objects/Unit.h"
#include "Engine/GameLoader.h"
UIManager::UIManager(DataManager* dataMan)
    : dataManRef(dataMan)
{}
void UIManager::SpawnTroop(Age age, UnitType type)
{
    if (age == Age::Arcade && type == UnitType::Melee) {
        sf::String path = "Assets/meleeUnitSprite.png";
        int unitCost = 25;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            Unit* newGuardian = new Unit(dataManRef->playerBase->frontOfBasePos, dataManRef, path, false, 0.75, 34,
                100, 0, 0, 0, 75, 100, 1, 1, 50, 50);

            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
    if (age == Age::Arcade && type == UnitType::Ranged) {
        sf::String path = "Assets/rangedUnitSprite.png";
        int unitCost = 50;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            Unit* newGuardian = new Unit(dataManRef->playerBase->frontOfBasePos, dataManRef, path, false, 0.75, 34,
                100, 1, 50, 300, 75, 150, 1, 2, 50, 50);
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
}
void UIManager::StartGame(Difficulty diff)
{
    dataManRef->gameLdrRef->LoadGame(diff);
}

void UIManager::MoveToScreen(GameScreen screen)
{
    dataManRef->SetGameScreen(screen);
}
