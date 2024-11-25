#pragma once
#include "UI/UIManager.h"
#include "UI/UIElements/Button.h"
#include "UI/UIElements/Queue.h"
#include "Enums/ShopState.h"
#include "Enums/Screen.h"
class DataManager;
class TextureLoader;

class UIRenderer
{
public:
	UIRenderer(UIManager* uiMan, DataManager* dataMan, sf::RenderWindow& win, TextureLoader* txrLdr);
	void SetPositions();
	void MoveUIWithCam(int pos);
	void Render();
	void DrawText(std::string inputText, int textSize, 
		sf::Color textCol, sf::Vector2f pos, bool centerPos = true);
	void DrawBar(sf::Vector2f barSize, sf::Vector2f barPos, float barPercentage,
		sf::Color barCol, bool centerPos = true);
	void DrawMenus();
	sf::String winText;

	Queue queue;
	void SetShopState(ShopState state);
	ShopState GetShopState();
	void SetInfoText(std::string text);
private:
	void CreateButton(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
		ShopState shopState, std::string info, bool center = false);
	void CreateButton(sf::Vector2i pos, sf::Texture& txr, std::function<void()> onClick,
		Screen screen, bool center = false);

	DataManager* dataManRef;
	sf::RenderWindow& window;
	UIManager* uiManRef;
	TextureLoader* txrLdrRef;

	sf::Font font;
	std::vector<Button> allButtons;
	std::vector<Button>& GetButtons();

	float GetCentredXPos();
	float GetCentredYPos();
	sf::Vector2i GetCentredPos();

	sf::Texture menuCornerTexture;
	sf::Sprite menuCornerSprite;
	sf::FloatRect menuCornerSize;

	sf::Texture menuMiddleTexture;
	sf::Sprite menuMiddleSprite;
	sf::FloatRect menuMiddleSize;

	ShopState currentShopState;

	sf::Vector2u windowSize;
	float statMenuMargin = 10;
	sf::Vector2i statsPos;
	sf::Vector2i statsSize;

	sf::Vector2i moneyTextPos;
	sf::Vector2i expTextPos;

	//queue is located between the player stats and store

	//info text is located below the queue
	float infoTextMargin = 5;
	sf::Vector2i infoTextPos;
	std::string infoText;
	void SetInfoTextFromButt();
	std::string GetInfoTextFromButt();
	//store is located at the right side of the screen
	sf::Vector2i storePos;
	sf::Vector2i storeSize;
};
