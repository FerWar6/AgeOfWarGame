#pragma once
#include <SFML/Graphics.hpp>
#include "Data/DataManager.h"
class CameraMovement
{
public:
	CameraMovement(sf::RenderWindow& win, sf::View& c, DataManager* dataMan);
	void UpdateCam();
	void MoveCam(int speed);
	int CalculateCamMoveSpeed(int distanceToBorder);
	void ResetCamPos();
	sf::Vector2i GetCamPos();
private:
	DataManager* dataManRef;
	sf::RenderWindow& window;
	sf::View& cam;
	sf::Vector2i mousePos;
	int moveDirection;
	int winWidth;
	int margin = 150;
};
