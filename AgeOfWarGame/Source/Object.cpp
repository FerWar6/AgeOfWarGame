#include "Object.h"

Object::Object(sf::Vector2f pos, DataManager* dataMan)
    : objectPos(pos),
    dataManRef(dataMan)
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
