#pragma once
#include "engine/engine.h"
#include "Data/DataManager.h"
#include "UI/UIManager.h"
#include "UI/UIElements/Button.h"

class UIRenderer
{
public:
	UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& window);
	void Render();
	void DrawText(std::string inputText, int textSize, 
		sf::Color textCol, float xpos, float ypos);
	void DrawText(std::string inputText, int textSize,
		sf::Color textCol, float xpos, bool isXCentered, float ypos, 
		bool isYCentered);
	void DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, sf::Color barCol);
	int winState;
private:
	void CreateButton(sf::Vector2f pos, sf::Texture& texture, std::function<void()> onClick, GameState state);
	DataManager* dataManRef;
	sf::RenderWindow& window;
	UIManager* uiManRef;

	sf::Texture button1Texture;
	sf::Texture button2Texture;
	sf::Texture button3Texture;
	sf::Font font;

	std::vector<Button*> allButtons;
	std::vector<Button*>& GetButtons();
	void AddButton(Button* button);
};
