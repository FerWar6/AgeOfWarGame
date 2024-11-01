#pragma once
#include "Engine/engine.h"
#include "UI/UIElements/QueueSlot.h"

class Unit;
class UIRenderer;
class DataManager;

class Queue
{
public:
    // Constructor
    Queue(sf::Vector2f pos, sf::Vector2f size, DataManager* dataMan);

    // Public Interface
    void DrawQueue(sf::RenderWindow& window);
    void UpdateQueue();
    void AddUnitToQueue(Unit* unit);
    std::vector<Unit*>& GetUnitQueue(); // Consider making this const if modifications are not needed

private:
    // Private Helper Functions
    void DrawQueueSlots(sf::RenderWindow& window, int filledSlots);
    void TrainUnit();
    Unit* GetFirstFromQueue();
    void RemoveFirstFromQueue();
    bool IsQueueEmpty();
    void SetUnitToTrain();
    sf::RectangleShape DrawSlot(bool fill, sf::Vector2f pos);
    void CalculateBarPercentage(float currentTime, float targetTime);

    // Member Variables
    DataManager* dataManRef; // Reference to data manager
    int maxUnits;            // Maximum units allowed in the queue
    std::vector<Unit*> unitQueue; // Vector of units in the queue

    // Queue Properties
    sf::Vector2f queuePos;      // Position of the queue
    sf::Vector2f queueSize;     // Size of the queue
    sf::Vector2f queueBarPos;   // Position of the queue's progress bar
    sf::Vector2f queueBarSize;  // Size of the queue's progress bar
    sf::Vector2f queueSlotsPos; // Position of the queue slots

    // Progress Bar Properties
    float currentBarPercentage; // Current percentage of the progress bar

    // Training Timer
    bool trainingUnit;          // Flag indicating if a unit is currently being trained
    float currentUnitTrainTime; // Time required to train the current unit
    sf::Clock queueClock;       // Clock for timing queue operations
};
