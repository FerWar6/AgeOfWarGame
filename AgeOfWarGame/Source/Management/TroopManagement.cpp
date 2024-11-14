#include "TroopManagement.h"

#include "Objects/Unit.h"
#include "Data/DataManager.h"
#include "Objects/Base.h"
#include "UI/UIElements/Queue.h"

TroopManagement::TroopManagement(DataManager* dataMan)
    : dataManRef(dataMan)
{}

void TroopManagement::SpawnTroop(Age age, UnitType type)
{
    if (age == Age::Arcade && type == UnitType::Melee) {
        sf::String path = "Assets/Units/testing";
        int unitCost = 10;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            Unit* newGuardian = new Unit(dataManRef->playerBase->frontOfBasePos, dataManRef, path,
                0.75, //melee cooldown
                34, //melee damage
                100, //melee sight range
                1, //ranged coo;down
                50, //ranged damage
                300, //ranged sight range
                75, //allie sight range
                150, //health
                0.5); //spawntime
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
    if (age == Age::Arcade && type == UnitType::Ranged) {
        //sf::String path = "Assets/Monsters/Goblin/Attack3.png";
        sf::String path = "Assets/Knight/sheets";
        int unitCost = 50;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            Unit* newGuardian = new Unit(dataManRef->playerBase->frontOfBasePos, dataManRef, path,
                0.75, //melee cooldown
                34, //melee damage
                100, //melee sight range
                1, //ranged coo;down
                50, //ranged damage
                300, //ranged sight range
                75, //allie sight range
                150, //health
                2); //spawntime
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
}

void TroopManagement::SpawnEnemyTroop(Age age, UnitType type)
{
    if (age == Age::Arcade && type == UnitType::Melee) {
        sf::String path = "Assets/Units/testing";
        Unit* newEnemy = new Unit(dataManRef->enemyBase->frontOfBasePos, dataManRef, path,
            0.75, //melee cooldown
            34, //melee damage
            100, //melee sight range
            1, //ranged coo;down
            50, //ranged damage
            300, //ranged sight range
            75, //allie sight range
            150, //health
            30, //money
            10); //experience
        dataManRef->MarkObjForAdd(newEnemy);
    }
}
