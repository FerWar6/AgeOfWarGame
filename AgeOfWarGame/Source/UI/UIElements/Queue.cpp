#include "Queue.h"
#include "UI/UIRenderer.h"
#include "Objects/Unit.h"
#include "Data/DataManager.h"

// Constructor
Queue::Queue(sf::Vector2f pos, sf::Vector2f size, DataManager* dataMan)
    : queuePos(pos),
    queueSize(size),
    dataManRef(dataMan),
    maxUnits(5),
    currentBarPercentage(0),
    currentUnitTrainTime(0),
    trainingUnit(false)
{
    float barMargin = 5;
    queueBarPos = sf::Vector2f(pos.x + barMargin, pos.y + barMargin);
    queueBarSize = sf::Vector2f(size.x - (barMargin * 2), 10);
    queueSlotsPos = sf::Vector2f(queueBarPos.x, queueBarPos.y + queueBarSize.y + barMargin);
}

// Public Interface
void Queue::UpdateQueue()
{
    if (!IsQueueEmpty()) {
        if (!trainingUnit) {
            SetUnitToTrain();
        }
        else {
            TrainUnit();
        }
    }
}

void Queue::DrawQueue(sf::RenderWindow& window)
{
    dataManRef->uiRenRef->DrawBar(queueBarSize, queueBarPos, IsQueueEmpty() ? 0 : currentBarPercentage, sf::Color::Red, false);
    DrawQueueSlots(window, GetUnitQueue().size());
}

void Queue::AddUnitToQueue(Unit* unit)
{
    GetUnitQueue().push_back(unit);
}

// Private Helper Functions
void Queue::DrawQueueSlots(sf::RenderWindow& window, int filledSlots)
{
    int spaceBetweenSlots = 25;
    for (int i = 0; i < maxUnits; ++i) {
        sf::Vector2f slotPos(queueSlotsPos.x + (spaceBetweenSlots * i), queueSlotsPos.y);
        window.draw(DrawSlot(i < filledSlots, slotPos));
    }
}

void Queue::TrainUnit()
{
    if (queueClock.getElapsedTime().asSeconds() >= currentUnitTrainTime) {
        dataManRef->MarkObjForAdd(GetFirstFromQueue());
        RemoveFirstFromQueue();
        trainingUnit = false;
    }
    CalculateBarPercentage(queueClock.getElapsedTime().asSeconds(), currentUnitTrainTime);
}

void Queue::SetUnitToTrain()
{
    currentUnitTrainTime = GetFirstFromQueue()->GetTrainTime();
    queueClock.restart();
    trainingUnit = true;
}

sf::RectangleShape Queue::DrawSlot(bool fill, sf::Vector2f pos)
{
    sf::RectangleShape slot;
    slot.setSize(sf::Vector2f(15, 15));
    slot.setPosition(pos);
    slot.setFillColor(fill ? sf::Color::Red : sf::Color::White);
    return slot;
}

std::vector<Unit*>& Queue::GetUnitQueue()
{
    return unitQueue;
}

void Queue::CalculateBarPercentage(float currentTime, float targetTime)
{
    float percentage = currentTime / targetTime;
    currentBarPercentage = percentage;
}

Unit* Queue::GetFirstFromQueue()
{
    return unitQueue.front();
}

void Queue::RemoveFirstFromQueue()
{
    if (!unitQueue.empty()) {
        unitQueue.erase(unitQueue.begin());
    }
}

bool Queue::IsQueueEmpty()
{
    return unitQueue.empty();
}
