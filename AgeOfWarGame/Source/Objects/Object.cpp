#include "Objects/Object.h"
#include "Data/ServiceLocator.h"

Object::Object(sf::FloatRect rect, bool hasColl)
    : dataManRef(sl::GetDataManager()),
    objRect(rect),
    hasCollision(hasColl)
{}
Object::Object(sf::Vector2f pos, sf::Vector2f size, bool hasColl)
    : dataManRef(sl::GetDataManager()),
    objRect(pos, size),
    hasCollision(hasColl)
{}
void Object::UpdateObj(){}
void Object::RenderObj(sf::RenderWindow& window) {}
void Object::OnCollision(Object* obj) {}
sf::Vector2f Object::GetPos()
{
    return objRect.getPosition();
}
sf::Vector2f Object::GetSize()
{
    return objRect.getSize();
}
sf::FloatRect Object::GetRect()
{
    return objRect;
}
void Object::SetPos(sf::Vector2f newPos) {
    objRect = sf::FloatRect(newPos.x, newPos.y, objRect.left, objRect.top);
}

void Object::SetSize(sf::Vector2f newSize)
{
    objRect = sf::FloatRect(objRect.width, objRect.height, newSize.x, newSize.y);
}
