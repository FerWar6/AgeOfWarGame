#pragma once
#include "Engine/engine.h"
#include "Data/DataManager.h"
#include "UI/UIManager.h"
#include "UI/UIElements/Button.h"
#include "UI/UIElements/Queue.h"

class UIRenderer
{
public:
	UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& window);
	void Render();
	void DrawText(std::string inputText, int textSize, 
		sf::Color textCol, sf::Vector2f pos, bool centerPos = true);
	void DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage, 
		sf::Color barCol, bool centerPos = true);
	void DrawMenus();
	sf::String winText;

	Queue queue;


private:
	void CreateButton(sf::Vector2f pos, sf::String path, std::function<void()> onClick, GameScreen state);
	DataManager* dataManRef;
	sf::RenderWindow& window;
	UIManager* uiManRef;

	sf::Font font;
	std::vector<Button*> allButtons;
	std::vector<Button*>& GetButtons();
	void AddButton(Button* button);

	float GetCentredXPos();
	float GetCentredYPos();
	sf::Vector2f GetCentredPos();

	sf::Texture menuCornerTexture;
	sf::Sprite menuCornerSprite;
	float menuCornerThickness;

	sf::Texture menuMiddleTexture;
	sf::Sprite menuMiddleSprite;
	float menuMiddleThickness;

};
