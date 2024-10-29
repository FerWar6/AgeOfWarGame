#pragma once
#include "Engine/engine.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Unit;
class Base;
class Object;
class UIRenderer;
class UIManager;

class DataManager {
public:
    DataManager(Engine* engine, sf::RenderWindow& window);
    void SetPointers(UIManager* uiMan, UIRenderer* uiRen);

    void SetGameState(GameState state);
    GameState GetGameState();
    sf::RenderWindow& window;
    void CreateEnemy(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        float melCooldown = 0.75, int melDamage = 34, float melSightRange = 100,
        float alSightRange = 75, int maxHealth = 100, float moveSpeed = 1, float spwnTime = 1,
        int money = 50, int exp = 50);

    void CreateGuardian(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        float melCooldown = 0.75, int melDamage = 34, float melSightRange = 100,
        float alSightRange = 75, int maxHealth = 100, float moveSpeed = 1, float spwnTime = 1,
        int money = 50, int exp = 50);

    void SetBase(Base* base);
    void AddGameObject(Object* obj);

    void MarkObjForAdd(Object* obj);
    void MarkObjForDel(Object* obj);
    void DeleteGameObject(Object* obj);
    void DamageUnit(Unit* markedUnit, int damage);

    template<typename T>
    void RemoveItemFromList(std::vector<T>& list, T item) {
        list.erase(std::remove(list.begin(), list.end(), item), list.end());
    }
    std::vector<Object*>& GetGameObjects();
    std::vector<Unit*>& GetEnemies();
    std::vector<Unit*>& GetGuardians();
    
    std::vector<Object*> gameObjects;
    std::vector<Object*> markedForAddition;
    std::vector<Object*> markedForDeletion;

    void AddDeleteObjs();
    Base* enemyBase;
    Base* playerBase;
    void DamageBase(Base* targerBase, int damage);

    Engine* engineRef;
    UIRenderer* uiRenRef;
    UIManager* uiManRef;

    int playerMoney;
    void AddMoney(int moneyAmount);
    int playerExperience;
    void AddExperience(int experienceAmount);

    void EndGame(bool won);
    void ClearGameData();

    sf::Texture placeHoldTexture;

    float inputCooldown = 0.25f;
    sf::Clock inputCooldownClock;
private:
};
