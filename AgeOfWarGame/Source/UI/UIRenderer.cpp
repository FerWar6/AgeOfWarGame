#include "UI/UIRenderer.h"
#include "Data/DataManager.h"

UIRenderer::UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& window)
    : uiManRef(uiMan),
    dataManRef(dataMan),
    window(window)
{
    menuAncorPoint = sf::Vector2f(GetCentredXPos(), 0);
    if (!menuMiddleTexture.loadFromFile("Assets/menuMiddle.png")) std::cerr << "Error loading menu Texture!" << std::endl;
    menuMiddleSprite.setTexture(menuMiddleTexture);
    if (!menuBorderTexture.loadFromFile("Assets/menuBorder.png")) std::cerr << "Error loading menu Texture!" << std::endl;
    menuBorderSprite.setTexture(menuBorderTexture);
    if (!font.loadFromFile("Assets/font.ttf")) {std::cerr << "Error loading font!" << std::endl;
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    //Spawning melee button
    sf::Vector2f ButtonPos1(menuAncorPoint.x + 50, menuAncorPoint.y + 50);
    sf::Vector2f ButtonPos2(menuAncorPoint.x + 125, menuAncorPoint.y + 50);
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

        DrawText("Money: " + std::to_string(dataManRef->GetPlayerMoney()), 30, sf::Color::White, sf::Vector2f(25, 25), false);
        DrawMenu();
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

void UIRenderer::DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, sf::Color barCol)
{
    sf::RectangleShape barBack(barSize);
    barBack.setOrigin(barSize.x / 2, barSize.y / 2);

    barBack.setPosition(barPos);
    barBack.setFillColor(sf::Color::White);
    window.draw(barBack);

    sf::Vector2f frontPos = sf::Vector2f(barSize.x * barPercentage, barSize.y);
    sf::RectangleShape barFront(frontPos);
    barFront.setOrigin(barSize.x / 2, barSize.y / 2);
    barFront.setPosition(barPos);
    barFront.setFillColor(barCol);
    window.draw(barFront);
}
void UIRenderer::DrawMenu()
{
    sf::Vector2f menuSize(GetCentredXPos(), 150);

    menuBorderSprite.setPosition(menuAncorPoint);
    window.draw(menuBorderSprite);

    float borderSpriteWidth = menuBorderSprite.getGlobalBounds().width;
    menuBorderSprite.setPosition(menuSize.x * 2 - borderSpriteWidth, menuAncorPoint.y);
    window.draw(menuBorderSprite);

    sf::Vector2f pos(menuAncorPoint.x + borderSpriteWidth, menuAncorPoint.y);
    menuMiddleSprite.setScale((menuSize.x - (borderSpriteWidth * 2)) / 15, 1);
    menuMiddleSprite.setPosition(pos);
    window.draw(menuMiddleSprite);
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
