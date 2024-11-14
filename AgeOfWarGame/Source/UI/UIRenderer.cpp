#include "UIRenderer.h"
#include "Data/DataManager.h"
#include "Management/TextureManagement.h"
#include <iostream>

UIRenderer::UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& win)
    : uiManRef(uiMan),
    dataManRef(dataMan),
    window(win),
    queue(dataMan)
{
    TextureManagement::LoadTextFromPath(menuMiddleTexture, "Assets/menuMiddle2.png");
    menuMiddleSprite.setTexture(menuMiddleTexture);
    TextureManagement::LoadTextFromPath(menuCornerTexture, "Assets/menuCorner2.png");
    menuCornerSprite.setTexture(menuCornerTexture);

    menuCornerThickness = menuCornerSprite.getGlobalBounds().width;
    menuMiddleThickness = menuMiddleSprite.getGlobalBounds().width;


    if (!font.loadFromFile("Assets/font.ttf")) {std::cerr << "Error loading font!" << std::endl;
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
}

void UIRenderer::SetPositions()
{
    queue.SetPositions();
    //Spawning melee button
    sf::Vector2f ButtonPos1(sf::Vector2f(900, 50));
    sf::Vector2f ButtonPos2(sf::Vector2f(975, 50));
    CreateButton(ButtonPos1, "Assets/Age1MeleeUnitButton.png", std::bind(&UIManager::SpawnTroop, uiManRef, Age::Arcade, UnitType::Melee), GameScreen::GameScreen);
    //Spawning ranged button
    CreateButton(ButtonPos2, "Assets/Age1RangedUnitButton.png", std::bind(&UIManager::SpawnTroop, uiManRef, Age::Arcade, UnitType::Ranged), GameScreen::GameScreen);



    //Start button
    CreateButton(GetCentredPos(), "Assets/StartButton.png", std::bind(&UIManager::StartGame, uiManRef, Difficulty::Easy), GameScreen::StartScreen);
    //Restart button
    CreateButton(GetCentredPos(), "Assets/RestartButton.png", std::bind(&UIManager::MoveToScreen, uiManRef, GameScreen::StartScreen), GameScreen::EndScreen);
}


void UIRenderer::Render()
{
    switch (dataManRef->GetGameScreen()) {
    case GameScreen::StartScreen:
        break;

    case GameScreen::GameScreen:

        //DrawText("Money: " + std::to_string(dataManRef->GetPlayerMoney()), 30, sf::Color::White, sf::Vector2f(25, 25), false);
        DrawMenus();
        break;

    case GameScreen::EndScreen:
        DrawText(winText, 100, sf::Color::Red, sf::Vector2f(GetCentredXPos(), 100));
        break;
    }

    for (auto& butt : GetButtons()) {
        if (dataManRef->GetGameScreen() == butt->buttonState) {
            butt->UpdateButton();
            butt->RenderButton();
        }
    }
}


void UIRenderer::DrawText(std::string inputText, int textSize, sf::Color textCol, sf::Vector2f pos, bool centerPos)
{
    sf::Text text;
    text.setFont(font);
    text.setString(inputText);
    text.setCharacterSize(textSize);
    text.setFillColor(textCol);
    sf::FloatRect textBounds = text.getLocalBounds();
    if(centerPos) text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text.setPosition(pos);

    window.draw(text);
}

void UIRenderer::DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, sf::Color barCol, bool centerPos)
{
    sf::RectangleShape barBack(barSize);
    if(centerPos) barBack.setOrigin(barSize.x / 2, barSize.y / 2);
    
    barBack.setPosition(barPos);
    barBack.setFillColor(sf::Color::White);
    window.draw(barBack);

    sf::Vector2f frontPos = sf::Vector2f(barSize.x * barPercentage, barSize.y);
    sf::RectangleShape barFront(frontPos);
    if (centerPos) barFront.setOrigin(barSize.x / 2, barSize.y / 2);
    barFront.setPosition(barPos);
    barFront.setFillColor(barCol);
    window.draw(barFront);
}
void UIRenderer::DrawMenus()
{
    float windowWidth = window.getSize().x;
    float menuHeight = menuMiddleSprite.getGlobalBounds().height;

    sf::Vector2f queuePos(windowWidth / 4, 0);
    sf::Vector2f queueSize(windowWidth - (windowWidth / 5 * 2 + windowWidth / 4), menuHeight / 2);

    //player stats are located at the top right
    float statMenuMargin = 10;
    sf::Vector2f playerStatsMenuPos(0, 0);
    sf::Vector2f playerStatsMenuSize(windowWidth / 4, menuHeight);

    sf::Vector2f moneyTextPos(playerStatsMenuPos.x + statMenuMargin , playerStatsMenuPos.y + statMenuMargin);
    sf::Vector2f expTextPos(playerStatsMenuPos.x + statMenuMargin, playerStatsMenuPos.y + statMenuMargin + 35);

    //queue is located between the player stats and store

    //info text is located below the queue
    float infoTextMargin = 5;
    sf::Vector2f infoTextPos(windowWidth / 4 + infoTextMargin, menuHeight / 2 + infoTextMargin);

    //store is located at the right side of the screen
    sf::Vector2f playerStoreMenuPos(windowWidth / 5 * 3, 0);
    sf::Vector2f playerStoreMenuSize(windowWidth / 5 * 2, menuHeight);

    //draw stat menu
    menuMiddleSprite.setScale((playerStatsMenuSize.x - menuCornerThickness) / menuMiddleThickness, 1);
    menuMiddleSprite.setPosition(playerStatsMenuPos);
    window.draw(menuMiddleSprite);

    menuCornerSprite.setScale(-1, 1);
    menuCornerSprite.setPosition(playerStatsMenuSize.x, 0);
    window.draw(menuCornerSprite);

    DrawText("Money: " + std::to_string(dataManRef->GetPlayerMoney()), 30, sf::Color::White, moneyTextPos, false);
    DrawText("exp: " + std::to_string(dataManRef->GetPlayerExperience()), 30, sf::Color::White, expTextPos, false);

    //draw queue
    queue.UpdateQueue();
    queue.DrawQueue(window);
    //background
    //sf::RectangleShape queue;
    //queue.setSize(sf::Vector2f(15, 15));
    //queue.setPosition(queueVisualPos);
    //queue.setFillColor(sf::Color::White);
    //window.draw(queue);

    //DrawBar(queueBarSize, queueBarPos, 0.5, sf::Color::Red, false);
    
    //draw info text
    DrawText("Info text here", 20, sf::Color::White, infoTextPos, false);

    //draw shop
    menuMiddleSprite.setScale((playerStoreMenuSize.x - menuCornerThickness) / menuMiddleThickness, 1);
    menuMiddleSprite.setPosition(playerStoreMenuPos.x + menuCornerThickness, playerStoreMenuPos.y);
    window.draw(menuMiddleSprite);

    menuCornerSprite.setScale(1, 1);
    menuCornerSprite.setPosition(playerStoreMenuPos.x, 0);
    window.draw(menuCornerSprite);
    //menuMiddleSprite.setScale(playerStoreMenuPos.x / 15, 1);
    //menuMiddleSprite.setPosition(menuAncorPoint);

    //menuBorderSprite.setScale(1, 1);
    //menuBorderSprite.setPosition(menuAncorPoint);
    //window.draw(menuBorderSprite);

    //float borderSpriteWidth = 

    //menuBorderSprite.setPosition(window.getSize().x, menuAncorPoint.y);
    //menuBorderSprite.setScale(-1, 1);
    //window.draw(menuBorderSprite);
}
void UIRenderer::CreateButton(sf::Vector2f pos, sf::String path, std::function<void()> onClick, GameScreen state)
{
    Button* newButton = new Button(pos, path, onClick, state, dataManRef);
    AddButton(newButton);
}
std::vector<Button*>& UIRenderer::GetButtons()
{
    return allButtons;
}

void UIRenderer::AddButton(Button* button)
{
    allButtons.push_back(button);
}

float UIRenderer::GetCentredXPos()
{
    return window.getSize().x / 2;
}

float UIRenderer::GetCentredYPos()
{
    return window.getSize().y / 2;
}

sf::Vector2f UIRenderer::GetCentredPos()
{
    sf::Vector2u windowSize = window.getSize();
    return sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
}
