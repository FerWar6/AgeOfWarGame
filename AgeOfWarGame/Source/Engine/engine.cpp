#include "Engine/engine.h"
#include "Objects/Object.h"
Engine::Engine(int strange)
    : currentGameScreen(GameScreen::StartScreen),
    gamePaused(false),
    textureLoader(),
    dataMan(this, window),
    gameLdr(&dataMan),
    uiMan(&dataMan),
    uiRen(&uiMan, &dataMan, window),
    troopMan(&dataMan),
    enemySpawner(3.5f, &dataMan)
{ 

    int width = 1200;
    int height = 500;
    std::string name = "AgeOfWar";
    window.create(sf::VideoMode(width, height), name);
    DebugLn("Constructed engine");
    uiRen.SetPositions();
    dataMan.SetPointers(&gameLdr, &uiMan, &uiRen, &uiRen.queue, &troopMan);
    Start();
}
void Engine::Start() {
    DebugLn("Started Engine");
    UpdateEngine();
}
void Engine::UpdateEngine()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                DebugLn("Closed Engine");
                window.close();
            }
        }
        if(!gamePaused) UpdateGame();
        RenderGame();
    }
}

void Engine::UpdateGame()
{
    if (!dataMan.markedForAddition.empty() || !dataMan.markedForDeletion.empty()) {
        dataMan.UpdateGameObjVector();
    }
    switch (currentGameScreen) {
    case GameScreen::StartScreen:
        break;

    case GameScreen::GameScreen:
        enemySpawner.UpdateSpawner();
        if (!dataMan.gameObjects.empty()) {
            for (auto& obj : dataMan.GetGameObjects()) {
                obj->UpdateObj();
            }
        }
        if (dataMan.dataCleared) dataMan.dataCleared = false;
        break;

    case GameScreen::EndScreen:
        if (!dataMan.dataCleared) dataMan.ClearGameData();
        break;
    }
}


void Engine::RenderGame() {
    window.clear();

    sf::Sprite testSprite;
    testSprite.setTexture(dataMan.placeHoldTexture);
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
    uiRen.Render();
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
    for (auto& obj : dataMan.GetGameObjects()) {
        obj->RenderObj(window);
    }
}

void Engine::RenderDeathScreen()
{
}
