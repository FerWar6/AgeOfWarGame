#include "UIRenderer.h"
#include "DataManager.h"

UIRenderer::UIRenderer(UIManager* uiMan, DataManager* dataMan, Engine* engine, sf::RenderWindow& window)
    : uiManRef(uiMan),
    dataManRef(dataMan),
    engineRef(engine),
    winState(0),
    window(window)
{
    if (!font.loadFromFile("Assets/font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    if (!button1Texture.loadFromFile("Assets/UnitsButton.png")) {
        std::cerr << "Error loading texture!" << std::endl;
    }
    Button* newButton = new Button(sf::Vector2f(20,20), sf::Vector2f(50,50), button1Texture, std::bind(&UIManager::SpawnTroop, uiManRef), dataManRef);
    AddButton(newButton);

}

void UIRenderer::Render()
{
    DrawText("Money: " + std::to_string(dataManRef->playerMoney), 30, sf::Color::White, 0, true, 25, false);

    if (winState == 1) {
        DrawText("YOU WIN!", 100, sf::Color::Green, 0, true, 0, true);
    }
    if (winState == 2) {
        DrawText("YOU LOSE :(", 100, sf::Color::Red, 0, true, 0, true);
    }
    for (auto& butt : GetButtons()) {
        butt->UpdateButton();
        butt->RenderButton();
    }
}

void UIRenderer::DrawText(std::string inputText, int textSize, sf::Color textCol, float xpos, float ypos)
{
    sf::Text text;
    text.setFont(font);
    text.setString(inputText);
    text.setCharacterSize(textSize);
    text.setFillColor(textCol);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text.setPosition(xpos, ypos);

    window.draw(text);
}

void UIRenderer::DrawText(std::string inputText, int textSize, sf::Color textCol, float xpos, bool isXCentered, float ypos, bool isYCentered)
{
    sf::Text text;
    text.setFont(font);
    text.setString(inputText);
    text.setCharacterSize(textSize);
    text.setFillColor(textCol);

    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2);

    sf::Vector2f textPos = sf::Vector2f(isXCentered ? windowSize.x / 2 : xpos, isYCentered ? windowSize.y / 2 : ypos);
    text.setPosition(textPos);
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
std::vector<Button*>& UIRenderer::GetButtons()
{
    return allButtons;
}

void UIRenderer::AddButton(Button* button)
{
    allButtons.push_back(button);
}