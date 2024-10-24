#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

class DataManager;
class EnemySpawner;

class Engine {
public:
	Engine(int width, int height, const char* windowName);
	void Start();
	void UpdateEngine();
	void UpdateGame();
	void InputCheck();
	void RenderGame();
	void StopGame(int won);
	sf::RenderWindow& GetWin();
private:
	bool gameIsRunning;
	sf::RenderWindow window;
	DataManager* dataMan;
	EnemySpawner* enemySpawner;
};