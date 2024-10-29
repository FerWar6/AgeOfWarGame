#include "Data/DataManager.h"
#include "Objects/Object.h"
#include "Objects/Unit.h"
#include "Objects/Base.h"
#include <algorithm>

DataManager::DataManager(Engine* engine, sf::RenderWindow& window)
    : playerMoney(100),
    playerExperience(0),
    engineRef(engine),
    window(window)
{
    if (!placeHoldTexture.loadFromFile("Assets/Background.png")) {
        std::cerr << "Error loading texture!" << std::endl;
    }
}

void DataManager::SetPointers(UIManager* uiMan, UIRenderer* uiRen)
{
    uiManRef = uiMan;
    uiRenRef = uiRen;
}

void DataManager::SetGameState(GameState state)
{
    engineRef->SetGameState(state);
}

GameState DataManager::GetGameState()
{
    return engineRef->GetGameState();
}

void DataManager::SetBase(Base* base)
{
    base->isEnemy ? enemyBase = base : playerBase = base;
}

void DataManager::AddGameObject(Object* obj)
{
    gameObjects.push_back(obj);
}

std::vector<Object*>& DataManager::GetGameObjects()
{
    return gameObjects;
}

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


void DataManager::AddDeleteObjs()
{
    // Add new objects
    if (!markedForAddition.empty()) {
        gameObjects.insert(gameObjects.end(), markedForAddition.begin(), markedForAddition.end());
        markedForAddition.clear();
    }

    // Delete marked objects
    if (!markedForDeletion.empty()) {
        for (Object* obj : markedForDeletion) {
            // Check if object exists in gameObjects before removing
            auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
            if (it != gameObjects.end()) {
                gameObjects.erase(it);
            }
            delete obj;  // Ensure the object is deleted only once
        }
        markedForDeletion.clear();
    }
}


void DataManager::DamageBase(Base* targerBase, int damage)
{
    targerBase->baseHealth -= damage;
    if (targerBase->baseHealth <= 0) {
        targerBase->isEnemy ? EndGame(true) : EndGame(false);
    }
}

void DataManager::AddMoney(int moneyAmount)
{
    playerMoney += moneyAmount;
}

void DataManager::AddExperience(int experienceAmount)
{
    playerExperience += experienceAmount;
}

void DataManager::EndGame(bool won)
{
    SetGameState(GameState::DeathScreen);
    if(won) std::cerr << "YOU WON!" << std::endl;
    if(!won) std::cerr << "YOU LOST!" << std::endl;
    ClearGameData();

}

//void DataManager::ClearGameData() {
//    // Delete objects marked for addition
//    for (Object* obj : markedForAddition) {
//        delete obj; // Only delete if not nullptr
//    }
//    markedForAddition.clear();
//
//    // Delete objects in gameObjects
//    for (Object* obj : gameObjects) {
//        delete obj; // Only delete if not nullptr
//    }
//    gameObjects.clear();
//
//    // Delete objects marked for deletion
//    for (Object* obj : markedForDeletion) {
//        delete obj; // Only delete if not nullptr
//    }
//    markedForDeletion.clear();
//}
void DataManager::ClearGameData() {
    // Create a temporary vector to hold all objects to be deleted
    std::vector<Object*> toDelete;

    // Move objects marked for addition into the temporary vector
    toDelete.insert(toDelete.end(), markedForAddition.begin(), markedForAddition.end());
    markedForAddition.clear();

    // Move objects in gameObjects into the temporary vector
    toDelete.insert(toDelete.end(), gameObjects.begin(), gameObjects.end());
    gameObjects.clear();

    // Move objects marked for deletion into the temporary vector
    toDelete.insert(toDelete.end(), markedForDeletion.begin(), markedForDeletion.end());
    markedForDeletion.clear();

    // Delete all objects in the temporary vector
    for (Object* obj : toDelete) {
        delete obj; // Safely delete each object
    }

    // Clear the temporary vector (not strictly necessary, but good practice)
    toDelete.clear();
}


void DataManager::CreateEnemy(sf::Vector2f pos, DataManager* man, 
    sf::Texture texture, float melCooldown, int melDamage, 
    float melSightRange, float alSightRange, int maxHealth, float moveSpeed, 
    float spwnTime, int money, int exp)
{
    Unit* newEnemy = new Unit(pos, man, texture, true, melCooldown, melDamage,
        melSightRange, alSightRange, maxHealth, moveSpeed, spwnTime, money, exp);
    MarkObjForAdd(newEnemy);
}

void DataManager::CreateGuardian(sf::Vector2f pos, DataManager* man,
    sf::Texture texture, float melCooldown, int melDamage,
    float melSightRange, float alSightRange, int maxHealth, float moveSpeed,
    float spwnTime, int money, int exp)
{
    Unit* newGuardian = new Unit(pos, man, texture, false, melCooldown, melDamage,
        melSightRange, alSightRange, maxHealth, moveSpeed, spwnTime, money, exp);
    MarkObjForAdd(newGuardian);
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
    if (obj == nullptr) return;  // Guard against nullptr
    auto& objects = GetGameObjects();

    // Only delete if it exists in the gameObjects
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        // Remove from gameObjects
        objects.erase(it);
        delete obj;  // Only delete after confirming it's removed
    }
}

template<typename T>
void RemoveItemFromList(std::vector<T>& list, T item) {
    list.erase(std::remove(list.begin(), list.end(), item), list.end());
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