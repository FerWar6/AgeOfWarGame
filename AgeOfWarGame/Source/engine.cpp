#include "engine.h"
#include "DataManager.h"
#include "Object.h"
#include "Unit.h"
#include "EnemeySpawner.h"
#include "UIManager.h"
#include "UIRenderer.h"
Engine::Engine(int width, int height, const char* windowName)
{
    gameIsRunning = true;
    window.create(sf::VideoMode(width, height), windowName);
    dataMan = new DataManager(100, width, height, this, window);
    uiMan = new UIManager(dataMan);
    uiRen = new UIRenderer(uiMan, dataMan, this, window);
    enemySpawner = new EnemySpawner(4, dataMan);
    dataMan->SetPointers(uiMan, uiRen);
    Start();
}
void Engine::Start() {
    UpdateEngine();
}
void Engine::UpdateEngine()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        InputCheck();
        if(gameIsRunning) UpdateGame();
        window.clear();
        RenderGame();
        window.display();
    }
}

void Engine::UpdateGame()
{
    enemySpawner->UpdateSpawner();
    for (auto& obj : dataMan->GetGameObjects()) {
        obj->UpdateObj();
    }
}


void Engine::RenderGame()
{
    for (auto& obj : dataMan->GetGameObjects()) {
        obj->RenderObj(window);
    }
    uiRen->Render();
}

void Engine::StopGame(int won)
{
    gameIsRunning = false;
    if (won == 1) uiRen->winState = 1;
    if (won == 2) uiRen->winState = 2;
}

sf::RenderWindow& Engine::GetWin()
{
    return window;
}

float inputCooldown = 0.25f;
sf::Clock inputCooldownClock;
void Engine::InputCheck() {

    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && inputCooldownClock.getElapsedTime().asSeconds() >= inputCooldown) {
    //    dataMan->CreateEnemy(sf::Vector2f(1200 - 150, 250), dataMan);
    //    inputCooldownClock.restart();
    //}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && inputCooldownClock.getElapsedTime().asSeconds() >= inputCooldown) {
        std::cout << "Number of game objects: " << dataMan->gameObjects.size() << std::endl;
        std::cout << "Number of enemies: " << dataMan->allEnemies.size() << std::endl;
        std::cout << "Number of guardians: " << dataMan->allGuardians.size() << std::endl;
        inputCooldownClock.restart();
    }
}