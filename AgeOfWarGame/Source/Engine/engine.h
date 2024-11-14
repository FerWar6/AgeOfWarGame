#pragma once

//#include "Enums/GameScreen.h"
//#include "Enums/Difficulty.h"
//#include "Enums/UnitType.h"
//#include "Enums/Age.h"
//#include "Management/TextureManagement.h"
#include "Engine/EngineExtentions/Debug.h"

#include <SFML/Graphics.hpp>

#include "Data/DataManager.h"
#include "Engine/GameLoader.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "Management/TroopManagement.h"
#include "Management/TextureLoader.h"
#include "EnemeySpawner/EnemeySpawner.h"

class Engine {
public:
	Engine(int strange);
	void Start();
	void UpdateEngine();
	void UpdateGame();
	void RenderGame();
	void SetGameScreen(GameScreen state);
	GameScreen GetGameScreen();

private:
	void RenderStartScreen();
	void RenderGameScreen();
	void RenderDeathScreen();

	bool gamePaused;
	sf::RenderWindow window;
	GameScreen currentGameScreen;
	DataManager dataMan;
	GameLoader gameLdr;
	UIManager uiMan;
	UIRenderer uiRen;
	TroopManagement troopMan;
	TextureLoader textureLoader;
	EnemySpawner enemySpawner;
};