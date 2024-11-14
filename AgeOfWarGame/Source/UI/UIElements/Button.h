#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "Enums/GameScreen.h"

class DataManager;
class Button {
public:
    Button(sf::Vector2f pos, sf::String path, std::function<void()> onClick, GameScreen state, DataManager* dataMan);
    void UpdateButton();
    void RenderButton();
    bool HoveringOver();
    bool IsClicking();
    void HandleClick();

    GameScreen buttonState;
private:
    sf::Texture texture;
    sf::Sprite buttonSprite;
    std::function<void()> OnClick;
    sf::Vector2f buttonPos;
    sf::Vector2i mousePos;
    DataManager* dataManRef;

};
