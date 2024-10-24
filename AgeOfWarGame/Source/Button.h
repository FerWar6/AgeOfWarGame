#pragma once
#include "engine.h"
#include <functional>
#include <SFML/Window.hpp>
#include <iostream>
class Button {
public:
    Button(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, std::function<void()> onClick);
    void UpdateButton();
    void RenderButton(sf::RenderWindow& window);
    bool isClicked();
    void HandleClick();

private:
    sf::Sprite buttonSprite;
    std::function<void()> OnClick;
    sf::Vector2f buttonPos;
    sf::Vector2f buttonSize;
    sf::Vector2i mousePos;

};
