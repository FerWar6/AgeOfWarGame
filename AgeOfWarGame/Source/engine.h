#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

class DataManager;

class Engine {
public:
	Engine(int width, int height, const char* windowName);
	void Start();
	void UpdateEngine();
	void UpdateGame();
	void InputCheck();
	void RenderGame();
	sf::RenderWindow& GetWin();
private:
	sf::RenderWindow window;
	DataManager* dataMan;
};