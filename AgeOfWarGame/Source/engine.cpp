#include "engine.h"
#include "DataManager.h"
#include "Object.h"
#include "Unit.h"
Engine::Engine(int width, int height, const char* windowName)
{
    window.create(sf::VideoMode(width, height), windowName);
    dataMan = new DataManager(100, width, height);
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
        UpdateGame();
        window.clear();
        RenderGame();
        window.display();
    }
}

void Engine::UpdateGame()
{
    for (auto& obj : dataMan->GetGameObjects()) {
        obj->UpdateObj();
    }
}


void Engine::RenderGame()
{
    for (auto& obj : dataMan->GetGameObjects()) {
        obj->RenderObj(window);
    }
}

sf::RenderWindow& Engine::GetWin()
{
    return window;
}

float inputCooldown = 0.25f;
sf::Clock inputCooldownClock;
void Engine::InputCheck() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && inputCooldownClock.getElapsedTime().asSeconds() >= inputCooldown) {
        dataMan->CreateEnemy(sf::Vector2f(1200 - 25, 250), dataMan);
        inputCooldownClock.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && inputCooldownClock.getElapsedTime().asSeconds() >= inputCooldown) {
        dataMan->CreateGuardian(sf::Vector2f(25, 250), dataMan);
        inputCooldownClock.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && inputCooldownClock.getElapsedTime().asSeconds() >= inputCooldown) {
        std::cout << "Number of game objects: " << dataMan->gameObjects.size() << std::endl;
        std::cout << "Number of enemies: " << dataMan->allEnemies.size() << std::endl;
        std::cout << "Number of guardians: " << dataMan->allGuardians.size() << std::endl;
        inputCooldownClock.restart();
    }
}