#include "Object.h"

Object::Object(sf::Vector2f pos, DataManager* dataMan, sf::Texture texture)
    : objectPos(pos),
    dataManRef(dataMan),
    objTexture(texture)
{
    dataManRef->AddGameObject(this);
}

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
