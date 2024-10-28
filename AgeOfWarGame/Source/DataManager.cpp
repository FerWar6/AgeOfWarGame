#include "DataManager.h"
#include "Object.h"
#include "Unit.h"
#include "Base.h"
#include "UIRenderer.h"
#include <algorithm>

DataManager::DataManager(int money, int width, int height, Engine* engine, sf::RenderWindow& window)
    : playerMoney(money),
    playerExperience(0),
    engineRef(engine),
    window(window)
{
    if (!placeHoldTexture.loadFromFile("Assets/Dino.png")) {
        std::cerr << "Error loading texture!" << std::endl;
    }
    CreateBase(sf::Vector2f(100, height / 2), 100, false);
    CreateBase(sf::Vector2f(width - 100, height / 2), 100, true);
}

void DataManager::SetPointers(UIManager* uiMan, UIRenderer* uiRen)
{
    uiManRef = uiMan;
    uiRenRef = uiRen;
}



void DataManager::CreateBase(sf::Vector2f pos, int health, bool enemy)
{
    Base* base = new Base(pos, this, placeHoldTexture, health, enemy);
    SetBase(base);
}

void DataManager::SetBase(Base* base)
{
    base->isEnemy ? enemyBase = base : playerBase = base;
}

// Function to add an enemy to the enemies vector
void DataManager::AddEnemy(Unit* enemy) {
    allEnemies.push_back(enemy);
}

// Function to add a guardian to the guardians vector
void DataManager::AddGuardian(Unit* guardian) {
    allGuardians.push_back(guardian);
}

void DataManager::AddGameObject(Object* obj)
{
    gameObjects.push_back(obj);
}

// Optional getters to access the enemy and guardian lists
std::vector<Unit*>& DataManager::GetEnemies() {
    return allEnemies;
}

std::vector<Unit*>& DataManager::GetGuardians() {
    return allGuardians;
}
std::vector<Object*>& DataManager::GetGameObjects()
{
    return gameObjects;
}

void DataManager::AddMoney(int moneyAmount)
{
    playerMoney += moneyAmount;
}

void DataManager::AddExperience(int experienceAmount)
{
    playerExperience += experienceAmount;
}

void DataManager::CreateEnemy(sf::Vector2f pos, DataManager* man, 
    sf::Texture texture, float melCooldown, int melDamage, 
    float melSightRange, float alSightRange, int maxHealth, float moveSpeed, 
    float spwnTime, int money, int exp)
{
    Unit* newEnemy = new Unit(pos, man, texture, true, melCooldown, melDamage,
        melSightRange, alSightRange, maxHealth, moveSpeed, spwnTime, money, exp);
    AddEnemy(newEnemy);
}

void DataManager::CreateGuardian(sf::Vector2f pos, DataManager* man,
    sf::Texture texture, float melCooldown, int melDamage,
    float melSightRange, float alSightRange, int maxHealth, float moveSpeed,
    float spwnTime, int money, int exp)
{
    Unit* newGuardian = new Unit(pos, man, texture, false, melCooldown, melDamage,
        melSightRange, alSightRange, maxHealth, moveSpeed, spwnTime, money, exp);
    AddGuardian(newGuardian);
}

void DataManager::DeleteUnit(Unit* markedUnit) {
    auto& units = markedUnit->isEnemy ? GetEnemies() : GetGuardians();
    RemoveItemFromList<Unit*>(units, markedUnit);
    DeleteGameObject(markedUnit);
}

void DataManager::DeleteGameObject(Object* obj) {
    auto& objects = GetGameObjects();
    RemoveItemFromList<Object*>(objects, obj);
    delete obj;
}
template<typename T>
void RemoveItemFromList(std::vector<T>& list, T item) {
    list.erase(std::remove(list.begin(), list.end(), item), list.end());
}
void DataManager::DamageUnit(Unit* markedUnit, int damage) {
    auto& units = markedUnit->isEnemy ? GetEnemies() : GetGuardians();

    // Find the unit and apply damage
    auto it = std::find(units.begin(), units.end(), markedUnit);
    if (it != units.end()) {
        (*it)->Damage(damage); // Apply damage to the unit
    }
}

