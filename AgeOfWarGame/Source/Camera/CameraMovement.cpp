#include "CameraMovement.h"
#include "Engine/EngineExtentions/Debug.h"
#include "Engine/engine.h"
CameraMovement::CameraMovement(sf::RenderWindow& win, sf::View& c, DataManager* dataMan)
	: cam(c),
	moveDirection(0),
	window(win),
	dataManRef(dataMan)
{}

void CameraMovement::UpdateCam()
{
	winWidth = window.getSize().x;
	mousePos = sf::Mouse::getPosition(window);
	//DebugLn(GetCamPos().x);
	if (mousePos.x < winWidth && mousePos.x > winWidth - margin) MoveCam(CalculateCamMoveSpeed(winWidth - mousePos.x));
	if (mousePos.x > 0 && mousePos.x < margin) MoveCam(-CalculateCamMoveSpeed(mousePos.x));
}

void CameraMovement::MoveCam(int speed) {
	float newCamPosX = GetCamPos().x + speed;
	float worldSize = dataManRef->engineRef->GetWorldSize();
	float windowWidth = window.getSize().x;

	if (newCamPosX < 0) {
		speed = -GetCamPos().x;
	}
	else if (newCamPosX > worldSize - windowWidth) {
		speed = (worldSize - windowWidth) - GetCamPos().x;
	}

	if (speed != 0) {
		cam.move(speed, 0);
		window.setView(cam);
		dataManRef->OnCamMove(GetCamPos().x);
	}
}


int CameraMovement::CalculateCamMoveSpeed(int distanceToBorder)
{
	const float maxSpeed = 15;
	float speed = maxSpeed * (1.0f - static_cast<float>(distanceToBorder) / margin);

	return speed;
}

void CameraMovement::ResetCamPos()
{
	cam.setCenter(cam.getSize().x / 2, cam.getSize().y / 2);
	window.setView(cam);
}

sf::Vector2i CameraMovement::GetCamPos()
{
	sf::Vector2f viewCenter = cam.getCenter();
	sf::Vector2f viewSize = cam.getSize();
	return sf::Vector2i(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
}

