#pragma once

#include <SFML/Graphics.hpp>

class DataManager;

class Object{
public:
	Object(sf::FloatRect rect, bool hasColl = false);
	Object(sf::Vector2f pos, sf::Vector2f size, bool hasColl = false);
	virtual void UpdateObj();
	virtual void RenderObj(sf::RenderWindow& win);
	virtual void OnCollision(Object* obj);
	bool hasCollision;
	sf::Vector2f GetPos();
	sf::Vector2f GetSize();
	sf::FloatRect GetRect();
	void SetPos(sf::Vector2f newPos);
	void SetSize(sf::Vector2f newSize);

private:
	sf::FloatRect objRect;
protected:
	DataManager* dataManRef;
};