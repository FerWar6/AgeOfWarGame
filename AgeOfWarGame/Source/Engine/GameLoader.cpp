#include "Engine/GameLoader.h"
GameLoader::GameLoader(DataManager* dataMan)
    : dataManRef(dataMan)
{
    CreateBase(sf::Vector2f(100, 500 / 2), 10, false);
    CreateBase(sf::Vector2f(900 - 100, 500 / 2), 10, true);
}
void GameLoader::CreateBase(sf::Vector2f pos, int health, bool enemy)
{
    Base* base = new Base(pos, dataManRef, dataManRef->placeHoldTexture, health, enemy);
    dataManRef->SetBase(base);
}
void GameLoader::LoadGame(Difficulty difficulty)
{
    switch (difficulty) {
    case Difficulty::Easy:
        break;

    case Difficulty::Hard:
        break;

    case Difficulty::Impossible:

        break;
    }
}