#include "UIRenderer.h"
#include "Data/DataManager.h"
#include "Management/TextureManagement.h"
#include "Textures/TextureLoader.h"
#include "Textures/TextureItem.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine/EngineExtentions/Debug.h"
UIRenderer::UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& win, TextureLoader* txrLdr)
    : uiManRef(uiMan),
    dataManRef(dataMan),
    window(win),
    queue(dataMan),
    txrLdrRef(txrLdr),
    currentShopState(ShopState::Base)
{
    if (!font.loadFromFile("Assets/font.ttf")) {std::cerr << "Error loading font!" << std::endl;
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
}

void UIRenderer::SetPositions()
{
    menuCornerSprite.setTexture(txrLdrRef->GetTexture("MenuCorner"));
    menuMiddleSprite.setTexture(txrLdrRef->GetTexture("MenuMiddle"));

    menuCornerSize = menuCornerSprite.getGlobalBounds();
    menuMiddleSize = menuMiddleSprite.getGlobalBounds();

    windowSize = window.getSize();

    //player stats are located at the top right
    statMenuMargin = 10;
    statsPos = sf::Vector2i(0, 0);
    statsSize = sf::Vector2i(windowSize.x / 4, menuCornerSize.height);

    moneyTextPos = sf::Vector2i(statsPos.x + statMenuMargin, statsPos.y + statMenuMargin);
    expTextPos = sf::Vector2i(statsPos.x + statMenuMargin, statsPos.y + statMenuMargin + 35);


    float infoTextMargin = 5;
    infoTextPos = sf::Vector2i(windowSize.x / 4 + infoTextMargin, menuCornerSize.height / 2 + infoTextMargin);

    //store is located at the right side of the screen
    storeSize = sf::Vector2i(menuCornerSize.width + menuMiddleSize.width, menuCornerSize.height);
    storePos = sf::Vector2i(windowSize.x - storeSize.x, 0);

    queue.SetPositions(sf::Vector2f(storeSize.x, storeSize.y));
    //Spawning melee button
    int buttonBorder = 10;
    int buttonSize = 80;
    sf::Vector2i ButtonPos1(storePos.x + (menuCornerSize.width + (buttonBorder / 2)), storePos.y + buttonBorder);
    sf::Vector2i ButtonPos2(ButtonPos1.x + buttonSize + buttonBorder, ButtonPos1.y);
    sf::Vector2i ButtonPos3(ButtonPos1.x + (buttonBorder * 2) + (buttonSize * 2), ButtonPos1.y);
    sf::Vector2i ButtonPos4(ButtonPos1.x + (buttonBorder * 3) + (buttonSize * 3), ButtonPos1.y);
    sf::Vector2i ButtonPos5(ButtonPos1.x + (buttonBorder * 4) + (buttonSize * 4), ButtonPos1.y);

    //-----------------------Base Shop Buttons------------------------------
    CreateButton(ButtonPos1, txrLdrRef->GetTexture("UnitsButton"),
        std::bind(&UIManager::OpenShopMenu, uiManRef, ShopState::Units),
        ShopState::Base, "Train Troops");

    CreateButton(ButtonPos5, txrLdrRef->GetTexture("UpgradeAgeButton"),
        std::bind(&UIManager::OpenShopMenu, uiManRef, ShopState::Units),
        ShopState::Base, "New Age");

    //-----------------------Units Shop Buttons------------------------------
    CreateButton(ButtonPos1, txrLdrRef->GetTexture("Unit1Button"),
        std::bind(&UIManager::SpawnTroop, uiManRef, Age::Arcade, UnitType::Melee),
        ShopState::Units, "10$ - Monk");

    CreateButton(ButtonPos2, txrLdrRef->GetTexture("Unit2Button"),
        std::bind(&UIManager::SpawnTroop, uiManRef, Age::Arcade, UnitType::Ranged),
        ShopState::Units, "20$ - Archer");

    CreateButton(ButtonPos3, txrLdrRef->GetTexture("Unit3Button"),
        std::bind(&UIManager::SpawnTroop, uiManRef, Age::Arcade, UnitType::Tank),
        ShopState::Units, "50$ - Big Knight");

    CreateButton(ButtonPos5, txrLdrRef->GetTexture("BackButton"),
        std::bind(&UIManager::OpenShopMenu, uiManRef, ShopState::Base),
        ShopState::Units, "Back to menu");

    //-----------------------Other UI------------------------------
    CreateButton(GetCentredPos(), txrLdrRef->GetTexture("StartButton"),
        std::bind(&UIManager::StartGame, uiManRef, Difficulty::Easy), Screen::StartScreen,true);

    CreateButton(GetCentredPos(), txrLdrRef->GetTexture("RestartButton"),
        std::bind(&UIManager::MoveToScreen, uiManRef, Screen::StartScreen), Screen::EndScreen, true);
}




void UIRenderer::Render()
{
    switch (dataManRef->GetScreen()) {
    case Screen::StartScreen:
        break;

    case Screen::Screen:

        DrawMenus();
        break;

    case Screen::EndScreen:
        DrawText(winText, 100, sf::Color::Red, sf::Vector2f(GetCentredXPos(), 100));
        break;
    }

    for (auto& butt : GetButtons()) {
        if (dataManRef->GetScreen() == butt.GetScreen()) {
            if(butt.GetShopState() == currentShopState || butt.GetShopState() == ShopState::None){
                butt.UpdateButton();
                butt.RenderButton();
            }
        }
    }
}
void UIRenderer::DrawMenus()
{
    //draw stat menu
    menuMiddleSprite.setScale((statsSize.x - menuCornerSize.width) / menuMiddleSize.width, 1);
    menuMiddleSprite.setPosition(statsPos.x, statsPos.y);
    window.draw(menuMiddleSprite);

    menuCornerSprite.setScale(-1, 1);
    menuCornerSprite.setPosition(statsPos.x + statsSize.x, 0);
    window.draw(menuCornerSprite);

    DrawText("Money: " + std::to_string(dataManRef->GetPlayerMoney()), 30, sf::Color::White, sf::Vector2f(moneyTextPos.x, moneyTextPos.y), false);
    DrawText("exp: " + std::to_string(dataManRef->GetPlayerExperience()), 30, sf::Color::White, sf::Vector2f(expTextPos.x, expTextPos.y), false);

    //draw queue
    queue.UpdateQueue();
    queue.DrawQueue(window);

    //draw info text
    SetInfoTextFromButt();
    //DebugLn(infoText);
    DrawText(infoText, 20, sf::Color::White, sf::Vector2f(infoTextPos.x, infoTextPos.y), false);

    //draw shop
    menuMiddleSprite.setScale((storeSize.x - menuCornerSize.width) / menuMiddleSize.width, 1);
    menuMiddleSprite.setPosition(storePos.x + menuCornerSize.width, storePos.y);
    window.draw(menuMiddleSprite);

    menuCornerSprite.setScale(1, 1);
    menuCornerSprite.setPosition(storePos.x, 0);
    window.draw(menuCornerSprite);
}
void UIRenderer::MoveUIWithCam(int pos)
{
    statsPos = sf::Vector2i(pos, 0);

    moneyTextPos = sf::Vector2i(statsPos.x + statMenuMargin, statsPos.y + statMenuMargin);
    expTextPos = sf::Vector2i(statsPos.x + statMenuMargin, statsPos.y + statMenuMargin + 35);


    float infoTextMargin = 5;
    infoTextPos = sf::Vector2i(statsPos.x + statsSize.x + infoTextMargin, menuCornerSize.height / 2 + infoTextMargin);

    //store is located at the right side of the screen
    storeSize = sf::Vector2i(menuCornerSize.width + menuMiddleSize.width, menuCornerSize.height);
    storePos = sf::Vector2i(pos + windowSize.x - storeSize.x, 0);

    queue.MoveQueue(pos);
    for (auto& butt : GetButtons()) {
        if (dataManRef->GetScreen() == butt.GetScreen()) {
            butt.UpdateButtonPos(pos);
        }
    }
    DrawMenus();
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
    text.setPosition(pos.x, pos.y);

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

void UIRenderer::SetShopState(ShopState state)
{
    currentShopState = state;
}
ShopState UIRenderer::GetShopState()
{
    return currentShopState;
}
void UIRenderer::SetInfoText(std::string text)
{
    infoText = text;
}
void UIRenderer::CreateButton(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick, ShopState shopState, std::string info, bool center)
{
    allButtons.emplace_back(pos, txr, onClick, shopState, info, center);
}

void UIRenderer::CreateButton(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick, Screen screen, bool center)
{
    allButtons.emplace_back(pos, txr, onClick, screen, center);
}

std::vector<Button>& UIRenderer::GetButtons()
{
    return allButtons;
}
float UIRenderer::GetCentredXPos()
{
    return window.getSize().x / 2;
}

float UIRenderer::GetCentredYPos()
{
    return window.getSize().y / 2;
}

sf::Vector2i UIRenderer::GetCentredPos()
{
    sf::Vector2u windowSize = window.getSize();
    return sf::Vector2i(windowSize.x / 2, windowSize.y / 2);
}

void UIRenderer::SetInfoTextFromButt()
{
    if (infoText != GetInfoTextFromButt()) {
        //DebugLn("current: " << infoText);
        //DebugLn("new: " << GetInfoTextFromButt());
        SetInfoText(GetInfoTextFromButt());
    }
}

std::string UIRenderer::GetInfoTextFromButt()
{
    for (auto& butt : GetButtons()) {
        if (butt.HoveringOver()) {
            return butt.GetInfoText();
        }
    }
    return "";
}
