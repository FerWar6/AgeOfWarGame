#include "DataManager.h"

#include "Engine/engine.h"
#include "Objects/Object.h"
#include "Objects/Units/Unit.h"
#include "Objects/Base.h"
#include "Management/TroopManagement.h"
#include "Textures/TextureLoader.h"
#include <algorithm>
#include "Data/ServiceLocator.h"
// Constructor
DataManager::DataManager(Engine* engine, sf::RenderWindow& window)
    : playerMoney(100),
    playerExperience(0),
    dataCleared(false),
    engineRef(engine),
    window(window),
    enemyBase(nullptr),
    playerBase(nullptr),
    gameLdrRef(nullptr),
    uiManRef(nullptr),
    uiRenRef(nullptr),
    queueRef(nullptr),
    troopManRef(nullptr),
    textureLdrRef(nullptr)
{
    sl::SetDataManager(this);
}

sf::Vector2u DataManager::GetWindowSize()
{
    return window.getSize();
}

// Game State Management
void DataManager::SetScreen(Screen state)
{
    engineRef->SetScreen(state);
}

Screen DataManager::GetScreen()
{
    return engineRef->GetScreen();
}

// UI Pointer Setup
void DataManager::SetPointers(GameLoader* loader, UIManager* uiMan, UIRenderer* uiRen, Queue* queue, TroopManagement* troop, TextureLoader* text)
{
    gameLdrRef = loader;
    uiManRef = uiMan;
    uiRenRef = uiRen;
    queueRef = queue;
    troopManRef = troop;
    textureLdrRef = text;
    groundPos = window.getSize().y - 50;
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

std::vector<Object*> DataManager::GetColliders()
{
    std::vector<Object*> vector;
    for (auto& obj : GetGameObjects()) {
        if (obj->hasCollision) {
            vector.push_back(obj);
        }
        return vector;
    }
}
std::vector<Object*> DataManager::GetColliders(Object* parObj)
{
    std::vector<Object*> vector;
    for (auto& obj : GetGameObjects()) {
        if (obj->hasCollision && obj != parObj) {
            vector.push_back(obj);
        }
        return vector;
    }
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
            if (unit->isEnemy && !unit->GetUnitStopped()) {
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
            if (!unit->isEnemy && !unit->GetUnitStopped()) {
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
    SetScreen(Screen::EndScreen);
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

void DataManager::OnCamMove(int camPos)
{
    uiRenRef->MoveUIWithCam(camPos);
}



template<typename T>
void RemoveItemFromList(std::vector<T>& list, T item) {
    list.erase(std::remove(list.begin(), list.end(), item), list.end());
}
