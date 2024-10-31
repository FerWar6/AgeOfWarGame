#pragma once
#include "Engine/engine.h"
#include "UI/UIElements/QueueSlot.h"

class Unit;
class UIRenderer;
class DataManager;
class Queue
{
public:
	Queue(sf::Vector2f pos, sf::Vector2f size, DataManager* dataMan);
	void DrawQueue(sf::RenderWindow& window);
	void DrawQueueSlots(sf::RenderWindow& window, int filledSlots);
	void UpdateQueue();
	void UpdateTrainQueue();
	QueueSlot GetFirstInQueue();
	void SetUnitToTrain();
	void AddUnitToQueue(Unit* unit);
	void CreateQueueSlots(sf::Vector2f pos);
	QueueSlot FindEmptySlot();
	sf::RectangleShape DrawSlot(bool fill, sf::Vector2f pos);
	std::vector<QueueSlot>& GetSlots();

private:
	bool QueueEmpty();
	bool QueueFull();
	DataManager* dataManRef;

	std::vector<QueueSlot> queueSlots;
	sf::Vector2f queuePos;
	sf::Vector2f queueSize;

	sf::Vector2f queueBarPos;
	sf::Vector2f queueBarSize;
	float currentBarPercentage;
	void CalculateBarPercentage(float currentTime, float targetTime);

	sf::Vector2f queueSlotsPos;

	bool trainingUnit;
	float currentUnitTrainTime;
	sf::Clock queueClock;
}; 


