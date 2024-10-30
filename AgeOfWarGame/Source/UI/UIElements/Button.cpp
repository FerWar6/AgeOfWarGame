#include "UI/UIElements/Button.h"
#include "Data/DataManager.h"

Button::Button(sf::Vector2f pos, sf::String path, std::function<void()> onClick, GameScreen state, DataManager* dataMan)
    : buttonPos(pos),
    OnClick(onClick),
    buttonState(state),
    dataManRef(dataMan)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading button texture!" << std::endl;
    }
    buttonSprite.setTexture(texture);

    sf::FloatRect buttonBounds = buttonSprite.getLocalBounds();
    buttonSprite.setOrigin(buttonBounds.width / 2, buttonBounds.height / 2);
    buttonSprite.setPosition(buttonPos);
}
void Button::UpdateButton()
{
    mousePos = sf::Mouse::getPosition(dataManRef->window);
    if (HoveringOver() && IsClicking() && dataManRef->inputCooldownClock.getElapsedTime().asSeconds() >= dataManRef->inputCooldown) {
        HandleClick();
        dataManRef->inputCooldownClock.restart();
    }
}

void Button::RenderButton()
{
    //std::cerr << IsClicking() << "  " << HoveringOver() << std::endl;
    if (HoveringOver() && IsClicking()) {
        buttonSprite.setColor(sf::Color(200, 200, 200));
    }
    else if (HoveringOver()) {
        buttonSprite.setColor(sf::Color(255, 255, 255));
    }
    else {
        buttonSprite.setColor(sf::Color(220, 220, 220));
    }



    buttonSprite.setPosition(buttonPos);
    dataManRef->window.draw(buttonSprite);
}

bool Button::HoveringOver() {
    return buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
bool Button::IsClicking()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
void Button::HandleClick() {
    if (OnClick) {
        OnClick();
    }
}
