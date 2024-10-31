#include "Data/DataManager.h"
#include "Objects/Object.h"
#include "Objects/Unit.h"
#include "Objects/Base.h"
#include <algorithm>

// Constructor
DataManager::DataManager(Engine* engine, sf::RenderWindow& window)
    : playerMoney(100),
    playerExperience(0),
    dataCleared(false),
    engineRef(engine),
    window(window)
{}

// Game State Management
void DataManager::SetGameScreen(GameScreen state)
{
    engineRef->SetGameScreen(state);
}

GameScreen DataManager::GetGameScreen()
{
    return engineRef->GetGameScreen();
}

// UI Pointer Setup
void DataManager::SetPointers(GameLoader* loader, UIManager* uiMan, UIRenderer* uiRen, Queue* queue)
{
    gameLdrRef = loader;
    uiManRef = uiMan;
    uiRenRef = uiRen;
    queueRef = queue;
}

// Game Object Management
void DataManager::AddGameObject(Object* obj)
{
    gameObjects.push_back(obj);
}

std::vector<Object*>& DataManager::GetGameObjects()
{
    return gameObjects;
}

void DataManager::MarkObjForAdd(Object* obj)
{
    markedForAddition.push_back(obj);

}

void DataManager::MarkObjForDel(Object* obj)
{
    markedForDeletion.push_back(obj);
}

void DataManager::DeleteGameObject(Object* obj) {
    auto& objects = GetGameObjects();

    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        objects.erase(it);
        delete obj;
    }
}

void DataManager::UpdateGameObjVector()
{
    if (!markedForAddition.empty()) {
        gameObjects.insert(gameObjects.end(), markedForAddition.begin(), markedForAddition.end());
        markedForAddition.clear();
    }

    if (!markedForDeletion.empty()) {
        for (Object* obj : markedForDeletion) {
            auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
            if (it != gameObjects.end()) {
                gameObjects.erase(it);
            }
            delete obj;
            obj = nullptr;
        }
        markedForDeletion.clear();
    }
}

// Retrieve Specific Game Objects
std::vector<Unit*>& DataManager::GetEnemies() {
    static std::vector<Unit*> enemies;

    enemies.clear();

    for (Object* obj : gameObjects) {
        if (Unit* unit = dynamic_cast<Unit*>(obj)) {
            if (unit->isEnemy) {
                enemies.push_back(unit);
            }
        }
    }

    return enemies;
}

std::vector<Unit*>& DataManager::GetGuardians() {
    static std::vector<Unit*> guardians;

    guardians.clear();

    for (Object* obj : gameObjects) {
        if (Unit* unit = dynamic_cast<Unit*>(obj)) {
            if (!unit->isEnemy) {
                guardians.push_back(unit);
            }
        }
    }

    return guardians;
}

// Base and Unit Management
void DataManager::SetBase(Base* base)
{
    base->isEnemy ? enemyBase = base : playerBase = base;
}

void DataManager::DamageBase(Base* targetBase, int damage)
{
    targetBase->AddHealth(-damage);
    if (targetBase->GetHealth() <= 0) {
        targetBase->isEnemy ? EndGame(true) : EndGame(false);
    }
}

void DataManager::DamageUnit(Unit* markedUnit, int damage) {
    auto& objs = GetGameObjects();

    auto it = std::find(objs.begin(), objs.end(), markedUnit);
    if (it != objs.end()) {
        Unit* unit = dynamic_cast<Unit*>(*it);
        if (unit) {
            unit->Damage(damage);
        }
    }
}

// Game End and Data Clearing
void DataManager::EndGame(bool won)
{
    SetGameScreen(GameScreen::EndScreen);
    if (won) uiRenRef->winText = "You Won!";
    if (!won) uiRenRef->winText = "You Lost :(";
}


void DataManager::ClearGameData() {

    for (Object* obj : markedForAddition) {
        delete obj;
        obj = nullptr;
    }
    markedForAddition.clear();

    std::vector<Object*> baseObjects;
    for (Object* obj : gameObjects) {
        if (dynamic_cast<Base*>(obj)) {
            baseObjects.push_back(obj); // Keep base objects
        }
        else {
            delete obj; // Delete non-base objects
            obj = nullptr;
        }
    }

    gameObjects = std::move(baseObjects); // Retain only base objects in gameObjects

    for (Object* obj : markedForDeletion) {
        delete obj;
        obj = nullptr;
    }
    markedForDeletion.clear();

    dataCleared = true;
}


int DataManager::GetPlayerMoney()
{
    return playerMoney;
}

int DataManager::GetPlayerExperience()
{
    return playerExperience;
}

void DataManager::SetPlayerMoney(int money)
{
    playerMoney = money;
}

void DataManager::SetPlayerExperience(int exp)
{
    playerExperience = exp;
}

void DataManager::AddPlayerMoney(int money)
{
    playerMoney += money;
}

void DataManager::AddPlayerExperience(int exp)
{
    playerExperience += exp;
}



template<typename T>
void RemoveItemFromList(std::vector<T>& list, T item) {
    list.erase(std::remove(list.begin(), list.end(), item), list.end());
}
