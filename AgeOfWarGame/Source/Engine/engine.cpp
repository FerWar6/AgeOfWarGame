#include "Engine/engine.h"
#include "Engine/GameLoader.h"
#include "Data/DataManager.h"
#include "Objects/Object.h"
#include "EnemeySpawner/EnemeySpawner.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
Engine::Engine(int width, int height, const char* windowName)
    : currentGameState(GameState::StartScreen)
{
    gamePaused = false;
    window.create(sf::VideoMode(width, height), windowName);
    dataMan = new DataManager(this, window);
    gameLdr = new GameLoader(dataMan);
    uiMan = new UIManager(dataMan);
    uiRen = new UIRenderer(uiMan, dataMan, window);
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
        if(!gamePaused) UpdateGame();
        RenderGame();
    }
}

void Engine::UpdateGame()
{
    if (!dataMan->markedForAddition.empty() || !dataMan->markedForDeletion.empty()) {
        dataMan->AddDeleteObjs();
    }
    switch (currentGameState) {
    case GameState::StartScreen:
  
        break;

    case GameState::GameScreen:
        enemySpawner->UpdateSpawner();
        if (!dataMan->gameObjects.empty()) {
            for (auto& obj : dataMan->GetGameObjects()) {
                obj->UpdateObj();
            }
        }
        break;

    case GameState::DeathScreen:
        
        break;
    }
}


void Engine::RenderGame() {
    window.clear();

    sf::Sprite testSprite;
    testSprite.setTexture(dataMan->placeHoldTexture);
    window.draw(testSprite);

    switch (currentGameState) {
    case GameState::StartScreen:
        RenderStartScreen();
        break;

    case GameState::GameScreen:
        RenderGameScreen();
        break;

    case GameState::DeathScreen:
        RenderDeathScreen();
        break;
    }
    uiRen->Render();
    window.display();
}

void Engine::SetGameState(GameState state)
{
    currentGameState = state;
}

GameState Engine::GetGameState()
{
    return currentGameState;
}

void Engine::RenderStartScreen()
{
}

void Engine::RenderGameScreen()
{
    for (auto& obj : dataMan->GetGameObjects()) {
        obj->RenderObj(window);
    }
}

void Engine::RenderDeathScreen()
{
}
