#include "HealthBar.h"
#include "engine.h"

HealthBar::HealthBar() {
}

void HealthBar::Draw(sf::Vector2f barSize, sf::Vector2f pos, float percentage, sf::RenderWindow& window) {
    sf::RectangleShape background(barSize);
    sf::Vector2f centerPos = sf::Vector2f(pos.x- barSize.x/2,pos.y- barSize.y/2);
    background.setPosition(centerPos);
    background.setFillColor(sf::Color::White);
    window.draw(background);

    sf::Vector2f healthSize(barSize.x * percentage, barSize.y);
    sf::RectangleShape health(healthSize);
    health.setPosition(centerPos);
    health.setFillColor(sf::Color::Red);
    window.draw(health);
}
