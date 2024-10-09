#pragma once
#include <SFML/Graphics.hpp>

class HealthBar {
public:
    HealthBar();
    void Draw(sf::Vector2f size, sf::Vector2f pos, float percentage, sf::RenderWindow& window);
private:
    sf::RectangleShape bar;
};
