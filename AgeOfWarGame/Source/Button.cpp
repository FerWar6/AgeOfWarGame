#include "Button.h"
#include "DataManager.h"
Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Texture& texture, std::function<void()> onClick)
    : buttonPos(pos),
    buttonSize(size),
    OnClick(onClick)
{
    buttonSprite.setTexture(texture);
    //buttonSprite.setTexture(texture);
}

void Button::UpdateButton()
{
    mousePos = sf::Mouse::getPosition();
    //if (isClicked()) {
    //    HandleClick();
    //}
    //std::cout << "I EXIST" << std::endl;

}

void Button::RenderButton(sf::RenderWindow& window)
{

    //sf::Sprite sprite;
    //sprite.setTexture(dataManRef->placeHoldTexture);

    //sprite.setPosition(400, 300);

    //window.draw(sprite);
    std::cout << "I EXIST" << std::endl;

    buttonSprite.setPosition(buttonPos);
    window.draw(buttonSprite);
}

//bool Button::isClicked() {
//    return buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
//}
//void Button::HandleClick() {
//    if (OnClick) {
//        OnClick();
//    }
//}