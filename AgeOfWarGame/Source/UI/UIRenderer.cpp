#include "UI/UIRenderer.h"
#include "Data/DataManager.h"

UIRenderer::UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& window)
    : uiManRef(uiMan),
    dataManRef(dataMan),
    winState(0),
    window(window)
{
    if (!font.loadFromFile("Assets/font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    //Spawning troop button
    if (!button1Texture.loadFromFile("Assets/UnitsButton2.png")) std::cerr << "Error loading texture!" << std::endl; 
    CreateButton(sf::Vector2f(20, 20), button1Texture, std::bind(&UIManager::SpawnTroop, uiManRef), GameState::GameScreen);
    //Start button
    if (!button2Texture.loadFromFile("Assets/StartButton.png")) std::cerr << "Error loading texture!" << std::endl;
    CreateButton(sf::Vector2f(50, 50), button2Texture, std::bind(&UIManager::StartGame, uiManRef), GameState::StartScreen);
    //Restart button
    if (!button3Texture.loadFromFile("Assets/RestartButton.png")) std::cerr << "Error loading texture!" << std::endl;
    CreateButton(sf::Vector2f(50, 50), button3Texture, std::bind(&UIManager::StartGame, uiManRef), GameState::DeathScreen);
}

void UIRenderer::Render()
{
    switch (dataManRef->GetGameState()) {
    case GameState::StartScreen:
        break;

    case GameState::GameScreen:

        DrawText("Money: " + std::to_string(dataManRef->playerMoney), 30, sf::Color::White, 0, true, 25, false);

        if (winState == 1) {
            DrawText("YOU WIN!", 100, sf::Color::Green, 0, true, 0, true);
        }
        if (winState == 2) {
            DrawText("YOU LOSE :(", 100, sf::Color::Red, 0, true, 0, true);
        }
        break;

    case GameState::DeathScreen:
        break;
    }

    for (auto& butt : GetButtons()) {
        if (dataManRef->GetGameState() == butt->buttonState) {
            butt->UpdateButton();
            butt->RenderButton();
        }
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
void UIRenderer::CreateButton(sf::Vector2f pos, sf::Texture& texture, std::function<void()> onClick, GameState state)
{
    Button* newButton = new Button(pos, sf::Vector2f(0, 0), texture, onClick, state, dataManRef);
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