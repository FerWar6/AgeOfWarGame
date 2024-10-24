#pragma once
#include "engine.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Unit;
class Base;
class Object;
class UIRenderer;

class DataManager {
public:
    DataManager(int money, int width, int height, Engine* engine, sf::RenderWindow& window);
    sf::RenderWindow& window;
    void CreateEnemy(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        float melCooldown = 0.75, int melDamage = 34, float melSightRange = 100,
        float alSightRange = 75, int maxHealth = 100, float moveSpeed = 1, float spwnTime = 1,
        int money = 50, int exp = 50);

    void CreateGuardian(sf::Vector2f pos, DataManager* man, sf::Texture texture,
        float melCooldown = 0.75, int melDamage = 34, float melSightRange = 100,
        float alSightRange = 75, int maxHealth = 100, float moveSpeed = 1, float spwnTime = 1,
        int money = 50, int exp = 50);

    void CreateBase(sf::Vector2f pos, int health, bool enemy);

    void SetBase(Base* base);
    void AddEnemy(Unit* enemy);
    void AddGuardian(Unit* guardian);
    void AddGameObject(Object* obj);

    void DeleteUnit(Unit* markedUnit);
    void DeleteGameObject(Object* obj);
    void DamageUnit(Unit* markedUnit, int damage);

    template<typename T>
    void RemoveItemFromList(std::vector<T>& list, T item) {
        list.erase(std::remove(list.begin(), list.end(), item), list.end());
    }

    std::vector<Unit*>& GetEnemies();
    std::vector<Unit*>& GetGuardians();
    std::vector<Object*>& GetGameObjects();

    std::vector<Unit*> allEnemies;
    std::vector<Unit*> allGuardians;
    std::vector<Object*> gameObjects;

    Base* enemyBase;
    Base* playerBase;

    Engine* engineRef;
    UIRenderer* uiRen;

    int playerMoney;
    void AddMoney(int moneyAmount);
    int playerExperience;
    void AddExperience(int experienceAmount);

    sf::Texture placeHoldTexture;
private:
};
