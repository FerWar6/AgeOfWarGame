#include "Button.h"
#include "DataManager.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, std::function<void()> onClick, DataManager* dataMan)
    : buttonPos(pos),
    buttonSize(size),
    OnClick(onClick),
    dataManRef(dataMan)
{
    buttonSprite.setTexture(texture);
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
        buttonSprite.setColor(sf::Color(150, 150, 150));
    }
    else if (HoveringOver()) {
        buttonSprite.setColor(sf::Color(200, 200, 200));
    }
    else {
        buttonSprite.setColor(sf::Color(255, 255, 255));
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
