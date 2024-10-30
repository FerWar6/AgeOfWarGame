#include "Objects/Object.h"

Object::Object(sf::Vector2f pos, DataManager* dataMan, sf::Texture texture)
    : objectPos(pos),
    dataManRef(dataMan),
    objTexture(texture)
{}

void Object::UpdateObj(){
}
void Object::RenderObj(sf::RenderWindow& win) {
}
sf::Vector2f Object::GetPos()
{
    return objectPos;
}
void Object::SetPos(sf::Vector2f newPos) {
    objectPos = newPos;
}
