#include "GameLoader.h"
#include "Objects/Base.h"
#include "Data/DataManager.h"
GameLoader::GameLoader(DataManager* dataMan)
    : dataManRef(dataMan)
{
    int width = 900;
    int height = 500;
    int margin = 100;
    CreateBase(sf::Vector2f(margin, height - margin), 50, false);
    CreateBase(sf::Vector2f(width - margin, height - margin), 50, true);
}
void GameLoader::CreateBase(sf::Vector2f pos, int health, bool enemy)
{
    Base* base = new Base(pos, dataManRef, dataManRef->placeHoldTexture, health, enemy);
    dataManRef->SetBase(base);
    dataManRef->MarkObjForAdd(base);
}
void GameLoader::LoadGame(Difficulty difficulty)
{
    switch (difficulty) {
    case Difficulty::Easy:
        dataManRef->playerBase->SetHealth(100);
        dataManRef->enemyBase->SetHealth(100);

        dataManRef->SetPlayerMoney(100);
        dataManRef->SetPlayerExperience(0);
        break;

    case Difficulty::Hard:
        dataManRef->playerBase->SetHealth(100);
        dataManRef->enemyBase->SetHealth(200);

        dataManRef->SetPlayerMoney(100);
        dataManRef->SetPlayerExperience(0);
        break;

    case Difficulty::Impossible:
        dataManRef->playerBase->SetHealth(100);
        dataManRef->enemyBase->SetHealth(400);

        dataManRef->SetPlayerMoney(100);
        dataManRef->SetPlayerExperience(0);
        break;
    }
    dataManRef->SetGameScreen(GameScreen::GameScreen);
}