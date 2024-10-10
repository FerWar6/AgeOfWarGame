#include "engine.h"
#include "DataManager.h"
#pragma once
class UIRenderer
{
public:
	UIRenderer(DataManager* dataMan, Engine* engine);
	void Render(sf::RenderWindow& window);
	int winState;
private:
	DataManager* dataManRef;
	Engine* engineRef;
	sf::Font font;
};
