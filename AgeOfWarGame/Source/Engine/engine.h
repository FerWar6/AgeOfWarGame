#pragma once

//#include "Enums/Screen.h"
//#include "Enums/Difficulty.h"
//#include "Enums/UnitType.h"
//#include "Enums/Age.h"
//#include "Textures/TextureManagement.h"
#include "Engine/EngineExtentions/Debug.h"

#include <SFML/Graphics.hpp>

#include "Data/DataManager.h"
#include "Engine/GameLoader.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "Management/TroopManagement.h"
#include "Textures/TextureLoader.h"
#include "EnemeySpawner/EnemeySpawner.h"
#include "Visuals/Background.h"
#include "Camera/CameraMovement.h"
#include "Data/ServiceLocator.h"
class Engine {
public:
	Engine(int strange);
	void Start();
	void UpdateEngine();
	void UpdateGame();
	void RenderGame();
	void UpdateCollision();
	void SetScreen(Screen state);
	Screen GetScreen();
	int GetWorldSize();
private:

	int winWidth = 1050;
	int winHeight = 750;
	int worldSize = 2500;
	std::string name = "AgeOfWar";

	void RenderStartScreen();
	void RenderScreen();
	void RenderDeathScreen();

	TextureLoader textureLoader;
	bool gamePaused;
	sf::RenderWindow window;
	sf::View cam;
	Screen currentScreen;
	DataManager dataMan;
	GameLoader gameLdr;
	UIManager uiMan;
	UIRenderer uiRen;
	TroopManagement troopMan;
	EnemySpawner enemySpawner;
	Background background;
	CameraMovement camMovement;
	sf::Clock gameClock;
	float accumulator = 0.0f;
	const float timeStep = 1.0f / 60; // 60 updates per second
	//const float timeStep = 1.0f / 12.0f; // 60 updates per second
};