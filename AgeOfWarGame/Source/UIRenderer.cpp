#include "UIRenderer.h"
UIRenderer::UIRenderer(DataManager* dataMan, Engine* engine)
	: dataManRef(dataMan),
	engineRef(engine),
    winState(0)
{
    if (!font.loadFromFile("Assets/font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
}

void UIRenderer::Render(sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(font);
    text.setString("Money: " + std::to_string(dataManRef->playerMoney));    
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f);
    window.draw(text);
    if (winState == 1) {
        //you win
        sf::Text text;
        text.setFont(font);
        text.setString("YOU WIN");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Green);
        text.setPosition(300, 100);
        window.draw(text);
    }
    if (winState == 2) {
        //you lose
        sf::Text text;
        text.setFont(font);
        text.setString("YOU LOSE");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Red);
        text.setPosition(300, 100);
        window.draw(text);
    }
}
