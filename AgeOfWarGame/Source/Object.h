#pragma once
#include "DataManager.h"
#include "engine.h"
#include "UIRenderer.h"

class Object{
public:
	Object(sf::Vector2f pos, DataManager* dataMan, sf::Texture texture);
	virtual void UpdateObj();
	virtual void RenderObj(sf::RenderWindow& win);
	DataManager* dataManRef;
	sf::Vector2f GetPos();
	void SetPos(sf::Vector2f newPos);
private:
	sf::Vector2f objectPos;
	sf::Texture objTexture;
protected:
};