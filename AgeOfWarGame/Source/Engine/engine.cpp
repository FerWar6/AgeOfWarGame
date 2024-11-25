#include "Engine/engine.h"
#include "Objects/Object.h"
#include <iostream>

Engine::Engine(int strange)
    : currentScreen(Screen::StartScreen),
    gamePaused(false),
    dataMan(this, window),
    textureLoader(),
    gameLdr(&dataMan),
    uiMan(&dataMan),
    uiRen(&uiMan, &dataMan, window, &textureLoader),
    troopMan(&dataMan),
    enemySpawner(3.5f, &dataMan),
    background(&textureLoader),
    camMovement(window, cam, &dataMan)
{ 
    window.create(sf::VideoMode(winWidth, winHeight), name);
    cam = sf::View(sf::FloatRect(0,0, winWidth, winHeight));
    window.setView(cam);
    uiRen.SetPositions();
    dataMan.SetPointers(&gameLdr, &uiMan, &uiRen, &uiRen.queue, &troopMan, &textureLoader);
    gameLdr.CreateBases();
    Start();
}
void Engine::Start() {
    UpdateEngine();
}
void Engine::UpdateEngine()
{
    while (window.isOpen()) {
        sf::Time elapsed = gameClock.restart();
        accumulator += elapsed.asSeconds();


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                DebugLn("Closed Engine");
                window.close();
            }
        }
        while (accumulator >= timeStep) {
            if (!gamePaused) UpdateGame();
            UpdateCollision();
            RenderGame();
            accumulator -= timeStep;
        }
    }
}


void Engine::UpdateGame()
{
    if (currentScreen == Screen::Screen) camMovement.UpdateCam();
    if (!dataMan.markedForAddition.empty() || !dataMan.markedForDeletion.empty()) {
        dataMan.UpdateGameObjVector();
    }
    switch (currentScreen) {
    case Screen::StartScreen:
        break;

    case Screen::Screen:
        enemySpawner.UpdateSpawner();
        if (!dataMan.gameObjects.empty()) {
            for (auto& obj : dataMan.GetGameObjects()) {
                obj->UpdateObj();
            }
        }
        if (dataMan.dataCleared) dataMan.dataCleared = false;
        break;

    case Screen::EndScreen:
        if (!dataMan.dataCleared) dataMan.ClearGameData();
        break;
    }
}


void Engine::RenderGame() {
    window.clear();
    background.Drawbg(window);

    switch (currentScreen) {
    case Screen::StartScreen:
        RenderStartScreen();
        break;

    case Screen::Screen:
        RenderScreen();
        break;

    case Screen::EndScreen:
        RenderDeathScreen();
        break;
    }
    uiRen.Render();
    window.display();
}

void Engine::UpdateCollision()
{
    for (auto& curObj : dataMan.GetColliders()) {
        for (auto& obj : dataMan.GetColliders(curObj)) {
            if (curObj->GetRect().intersects(obj->GetRect())) {
                obj->OnCollision(curObj);
            }
        }
    }
}

void Engine::SetScreen(Screen state)
{
    currentScreen = state;
    camMovement.ResetCamPos();
}

Screen Engine::GetScreen()
{
    return currentScreen;
}

int Engine::GetWorldSize()
{
    return worldSize;
}

void Engine::RenderStartScreen()
{
}

void Engine::RenderScreen()
{
    for (auto& obj : dataMan.GetGameObjects()) {
        obj->RenderObj(window);
    }
}

void Engine::RenderDeathScreen()
{
}
