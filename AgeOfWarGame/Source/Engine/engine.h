#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Enums/GameState.h"
#include "Enums/Difficulty.h"

class DataManager;
class EnemySpawner;
class UIManager;
class UIRenderer;
class GameLoader;

class Engine {
public:
	Engine(int width, int height, const char* windowName);
	void Start();
	void UpdateEngine();
	void UpdateGame();
	void RenderGame();
	void SetGameState(GameState state);
	GameState GetGameState();

private:
	void RenderStartScreen();
	void RenderGameScreen();
	void RenderDeathScreen();

	bool gamePaused;
	sf::RenderWindow window;
	DataManager* dataMan;
	GameLoader* gameLdr;
	EnemySpawner* enemySpawner;
	UIManager* uiMan;
	UIRenderer* uiRen;
	GameState currentGameState;
};