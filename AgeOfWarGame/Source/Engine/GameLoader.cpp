#include "GameLoader.h"
#include "Objects/Base.h"
#include "Data/DataManager.h"
#include "Engine/engine.h"
GameLoader::GameLoader(DataManager* dataMan)
    : dataManRef(dataMan)
{}
void GameLoader::CreateBases()
{
    int groundPos = 50;
    int margin = 100;
    int winHeight = dataManRef->GetWindowSize().y;

    sf::Vector2f playerPos = sf::Vector2f(margin, winHeight - groundPos);
    sf::Vector2f enemyPos = sf::Vector2f(dataManRef->engineRef->GetWorldSize() - margin, winHeight - groundPos);

    sf::Vector2f size = sf::Vector2f(10, 10);
    CreateBase(sf::FloatRect(playerPos, size), 50, false);
    CreateBase(sf::FloatRect(enemyPos, size), 50, true);
}
void GameLoader::CreateBase(sf::FloatRect rect, int health, bool enemy)
{
    Base* base = new Base(rect, health, enemy);
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
    dataManRef->SetScreen(Screen::Screen);
}