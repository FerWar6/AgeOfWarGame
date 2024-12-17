#include "TroopManagement.h"

#include "Objects/Units/MeleeUnit.h"
#include "Objects/Units/RangedUnit.h"
#include "Data/DataManager.h"
#include "Objects/Base.h"
#include "UI/UIElements/Queue.h"
#include "Textures/TextureLoader.h"
#include "Textures/SpriteSheet.h"
#include "Engine/EngineExtentions/Debug.h"

TroopManagement::TroopManagement(DataManager* dataMan)
    : dataManRef(dataMan)
{}

void TroopManagement::SpawnTroop(Age age, UnitType type)
{
    sf::Vector2f pos = sf::Vector2f(dataManRef->playerBase->frontOfBasePos.x, dataManRef->playerBase->frontOfBasePos.y);
    sf::Vector2f size = sf::Vector2f(10, 10);
    if (age == Age::Arcade && type == UnitType::Melee) {
        SpriteSheet& unitSheet = dataManRef->textureLdrRef->GetSpriteSheet("Unit1Sheet");
        int unitCost = 10;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            MeleeUnit* newGuardian = new MeleeUnit(sf::FloatRect(pos, size), unitSheet,
                0.75, //melee cooldown
                34, //melee damage
                100, //melee sight range
                75, //allie sight range
                150, //health
                0.5); //spawntime
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
    if (age == Age::Arcade && type == UnitType::Ranged) {
        SpriteSheet& unitSheet = dataManRef->textureLdrRef->GetSpriteSheet("Unit2Sheet");
        int unitCost = 20;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            RangedUnit* newGuardian = new RangedUnit(sf::FloatRect(pos, size), unitSheet,
                0.75, //melee cooldown
                34, //melee damage
                100, //melee sight range
                1, //ranged cooldown
                50, //ranged damage
                300, //ranged sight range
                75, //allie sight range
                100, //health
                1); //spawntime
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
    if (age == Age::Arcade && type == UnitType::Tank) {
        SpriteSheet& unitSheet = dataManRef->textureLdrRef->GetSpriteSheet("Unit3Sheet");
        int unitCost = 50;
        if (dataManRef->GetPlayerMoney() >= unitCost) {
            MeleeUnit* newGuardian = new MeleeUnit(sf::FloatRect(pos, size), unitSheet,
                1, //melee cooldown
                50, //melee damage
                100, //melee sight range
                75, //allie sight range
                300, //health
                1.5); //spawntime
            dataManRef->queueRef->AddUnitToQueue(newGuardian);
            dataManRef->AddPlayerMoney(-unitCost);
        }
    }
}

void TroopManagement::SpawnEnemyTroop(Age age, UnitType type)
{
    sf::Vector2f pos = sf::Vector2f(dataManRef->enemyBase->frontOfBasePos.x, dataManRef->enemyBase->frontOfBasePos.y);
    sf::Vector2f size = sf::Vector2f(10, 10);
    if (age == Age::Arcade && type == UnitType::Melee) {
        SpriteSheet& unitSheet = dataManRef->textureLdrRef->GetSpriteSheet("Unit3Sheet");
        MeleeUnit* newEnemy = new MeleeUnit(sf::FloatRect(pos, size), unitSheet,
            1, //melee cooldown
            50, //melee damage
            100, //melee sight range
            75, //allie sight range
            300, //health
            30, //money
            10); //experience
        dataManRef->MarkObjForAdd(newEnemy);
        //DebugLn("spawned enemy at pos: " << dataManRef->enemyBase->frontOfBasePos.x << "x" << dataManRef->enemyBase->frontOfBasePos.y);
    }
}
