#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Enums/Screen.h"
#include "Enums/ShopState.h"

class DataManager;
class Button {
public:
    Button(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
        Screen screen, bool center);
    Button(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
        ShopState state, std::string info, bool center);
    void UpdateButton();
    void RenderButton();
    bool HoveringOver();
    bool IsClicking();
    void HandleClick();

    void UpdateButtonPos(int pos);

    ShopState GetShopState();
    Screen GetScreen();
    std::string GetInfoText();
private:
    void Start();
    bool centered;
    sf::Texture& buttonTxr;
    sf::Sprite buttonSprite;
    std::function<void()> OnClick;

    sf::Vector2f buttonPos;
    sf::Vector2f baseButtonPos;
    sf::Vector2i mousePos;

    DataManager* dataManRef;
    ShopState shopState;
    Screen gameScreen;
    std::string infoText;
};
