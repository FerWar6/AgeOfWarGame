#include "Engine/engine.h"
#include "Engine/GameLoader.h"
#include "Data/DataManager.h"
#include "Objects/Object.h"
#include "EnemeySpawner/EnemeySpawner.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "Management/TroopManagement.h"
Engine::Engine(int width, int height, const char* windowName)
    : currentGameScreen(GameScreen::StartScreen)
{
    gamePaused = false;
    window.create(sf::VideoMode(width, height), windowName);
    dataMan = new DataManager(this, window);
    gameLdr = new GameLoader(dataMan);
    uiMan = new UIManager(dataMan);
    uiRen = new UIRenderer(uiMan, dataMan, window);
    enemySpawner = new EnemySpawner(4, dataMan);
    troopManRef = new TroopManagement(dataMan);
    dataMan->SetPointers(gameLdr, uiMan, uiRen, &uiRen->queue, troopManRef);
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
        dataMan->UpdateGameObjVector();
    }
    switch (currentGameScreen) {
    case GameScreen::StartScreen:
        break;

    case GameScreen::GameScreen:
        enemySpawner->UpdateSpawner();
        if (!dataMan->gameObjects.empty()) {
            for (auto& obj : dataMan->GetGameObjects()) {
                obj->UpdateObj();
            }
        }
        if (dataMan->dataCleared) dataMan->dataCleared = false;
        break;

    case GameScreen::EndScreen:
        if (!dataMan->dataCleared) dataMan->ClearGameData();
        break;
    }
}


void Engine::RenderGame() {
    window.clear();

    sf::Sprite testSprite;
    testSprite.setTexture(dataMan->placeHoldTexture);
    window.draw(testSprite);

    switch (currentGameScreen) {
    case GameScreen::StartScreen:
        RenderStartScreen();
        break;

    case GameScreen::GameScreen:
        RenderGameScreen();
        break;

    case GameScreen::EndScreen:
        RenderDeathScreen();
        break;
    }
    uiRen->Render();
    window.display();
}

void Engine::SetGameScreen(GameScreen state)
{
    currentGameScreen = state;
}

GameScreen Engine::GetGameScreen()
{
    return currentGameScreen;
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
