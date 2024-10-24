#include "engine.h"
#include "DataManager.h"
#include "Button.h"
#pragma once
class UIRenderer
{
public:
	UIRenderer(DataManager* dataMan, Engine* engine, sf::RenderWindow& window);
	void Render();
	void DrawText(std::string inputText, int textSize, 
		sf::Color textCol, float xpos, float ypos);
	void DrawText(std::string inputText, int textSize,
		sf::Color textCol, float xpos, bool isXCentered, float ypos, 
		bool isYCentered);
	void DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, sf::Color barCol);
	int winState;
	void OnClick();
private:
	DataManager* dataManRef;
	sf::RenderWindow& window;
	Engine* engineRef;
	sf::Font font;
	sf::Sprite sprite;

	std::vector<Button*> allButtons;
	std::vector<Button*>& GetButtons();
	void AddButton(Button* button);
};
