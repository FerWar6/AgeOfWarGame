#pragma once
#include "engine.h"
#include "DataManager.h"
#include "UIManager.h"
#include "Button.h"

class UIRenderer
{
public:
	UIRenderer(UIManager* uiMan, DataManager* dataMan, Engine* engine, sf::RenderWindow& window);
	void Render();
	void DrawText(std::string inputText, int textSize, 
		sf::Color textCol, float xpos, float ypos);
	void DrawText(std::string inputText, int textSize,
		sf::Color textCol, float xpos, bool isXCentered, float ypos, 
		bool isYCentered);
	void DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, sf::Color barCol);
	int winState;
private:

	DataManager* dataManRef;
	sf::RenderWindow& window;
	Engine* engineRef;
	UIManager* uiManRef;

	sf::Texture button1Texture;
	sf::Font font;

	std::vector<Button*> allButtons;
	std::vector<Button*>& GetButtons();
	void AddButton(Button* button);
};
