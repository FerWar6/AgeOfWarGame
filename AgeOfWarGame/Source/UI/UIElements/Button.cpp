#include "Button.h"
#include "Data/DataManager.h"
#include "Data/ServiceLocator.h"
#include "Management/TextureManagement.h"
#include "Textures/TextureItem.h"
#include "UI/UIRenderer.h"

Button::Button(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
    Screen screen, bool center)
    : buttonPos(pos),
    baseButtonPos(buttonPos),
    buttonTxr(txr),
    OnClick(onClick),
    shopState(ShopState::None),
    gameScreen(screen),
    centered(center),
    dataManRef(sl::GetDataManager()),
    infoText("")
{
    Start();
}
Button::Button(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
    ShopState state, std::string info, bool center)
    : buttonPos(pos),
    baseButtonPos(buttonPos),
    buttonTxr(txr),
    OnClick(onClick),
    shopState(state),
    gameScreen(Screen::Screen),
    centered(center),
    dataManRef(sl::GetDataManager()),
    infoText(info)
{
    Start();
}

void Button::Start()
{
    buttonSprite.setTexture(buttonTxr);
    buttonSprite.setPosition(buttonPos);
    sf::FloatRect buttonBounds = buttonSprite.getLocalBounds();
    if (centered) buttonSprite.setOrigin(buttonBounds.width / 2, buttonBounds.height / 2);
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
    buttonSprite.setPosition(buttonPos);
    if (HoveringOver() && IsClicking()) {
        buttonSprite.setColor(sf::Color(200, 200, 200));
    }
    else if (HoveringOver()) {
        buttonSprite.setColor(sf::Color(255, 255, 255));
    }
    else {
        buttonSprite.setColor(sf::Color(220, 220, 220));
    }
    dataManRef->window.draw(buttonSprite);
}

bool Button::HoveringOver() {
    if (GetShopState() == ShopState::None || GetShopState() == dataManRef->uiRenRef->GetShopState())
    {
        buttonSprite.setPosition(baseButtonPos);
        bool isHoveringOver = buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        buttonSprite.setPosition(buttonPos);
        return isHoveringOver;
    }
    return false;
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

ShopState Button::GetShopState()
{
    return shopState;
}

Screen Button::GetScreen()
{
    return gameScreen;
}

std::string Button::GetInfoText()
{
    return infoText;
}



void Button::UpdateButtonPos(int pos)
{
    buttonPos = sf::Vector2f(baseButtonPos.x + pos, baseButtonPos.y);
    buttonSprite.setPosition(buttonPos);
}
