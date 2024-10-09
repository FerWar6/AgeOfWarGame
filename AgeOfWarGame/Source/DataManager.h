#pragma once
#include "engine.h"
//#include "Object.h"
//#include "Unit.h"
//#include "Base.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Unit;
class Base;
class Object;

class DataManager {
public:
    DataManager() {};
    DataManager(int money, int width, int height);
    sf::RenderWindow window;
    void CreateEnemy(sf::Vector2f pos, DataManager* man, int health = 100, float speed = 1.0f,
        int meleeDmg = 10, float meleeAtckSpd = 1.0f,
        int rangedDmg = 15, float rangedAtckSpd = 1.0f,
        float sightRnge = 100.0f, float spwnTime = 1.0f,
        int exp = 0, int money = 0);

    void CreateGuardian(sf::Vector2f pos, DataManager* man, int health = 100, float speed = 1.0f,
        int meleeDmg = 10, float meleeAtckSpd = 1.0f,
        int rangedDmg = 15, float rangedAtckSpd = 1.0f,
        float sightRnge = 100.0f, float spwnTime = 1.0f,
        int exp = 0, int money = 0);

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

private:
    int playerMoney;
};
