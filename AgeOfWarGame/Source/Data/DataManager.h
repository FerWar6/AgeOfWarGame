#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Enums/GameScreen.h"

// Forward declarations
class Engine;
class Unit;
class Base;
class Object;
class GameLoader;
class UIRenderer;
class UIManager;
class Queue;
class TroopManagement;

class DataManager {
public:
    // Constructor
    DataManager(Engine* engine, sf::RenderWindow& window);

    // Public Member Variables (to remain public as specified)
    sf::RenderWindow& window;
    sf::Vector2u GetWindowSize();
    // Game State Management
    void SetGameScreen(GameScreen state);
    GameScreen GetGameScreen();

    // UI Pointer Setup
    void SetPointers(GameLoader* loader, UIManager* uiMan, UIRenderer* uiRen, 
        Queue* queue, TroopManagement* troop);

    // Game Object Management
    void AddGameObject(Object* obj);
    std::vector<Object*>& GetGameObjects();
    void MarkObjForAdd(Object* obj);
    void MarkObjForDel(Object* obj);
    void DeleteGameObject(Object* obj);
    void UpdateGameObjVector();

    // Retrieve Specific Game Objects
    std::vector<Unit*>& GetEnemies();
    std::vector<Unit*>& GetGuardians();

    // Base References
    Base* enemyBase;
    Base* playerBase;

    // Base and Unit Management
    void SetBase(Base* base);
    void DamageBase(Base* targetBase, int damage);
    void DamageUnit(Unit* markedUnit, int damage);

    // Game End and Data Clearing
    void EndGame(bool won);
    void ClearGameData();
    bool dataCleared;
    // Public Utility Methods
    template<typename T>
    void RemoveItemFromList(std::vector<T>& list, T item) {
        list.erase(std::remove(list.begin(), list.end(), item), list.end());
    }
    // Engine and UI References
    Engine* engineRef;
    GameLoader* gameLdrRef;
    UIRenderer* uiRenRef;
    UIManager* uiManRef;
    Queue* queueRef;
    TroopManagement* troopManRef;
    // Resource and Timing Management
    float inputCooldown = 0.25f;
    sf::Clock inputCooldownClock;

    // Object Management Vectors
    std::vector<Object*> gameObjects;
    std::vector<Object*> markedForAddition;
    std::vector<Object*> markedForDeletion;

    sf::Texture placeHoldTexture;

    int GetPlayerMoney();
    int GetPlayerExperience();

    void SetPlayerMoney(int money);
    void SetPlayerExperience(int exp);

    void AddPlayerMoney(int money);
    void AddPlayerExperience(int exp);
private:

    int playerMoney;
    int playerExperience;

};
