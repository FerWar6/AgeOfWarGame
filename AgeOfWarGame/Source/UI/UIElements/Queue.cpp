#include "Queue.h"
#include "UI/UIRenderer.h"
#include "Objects/Units/Unit.h"
#include "Data/DataManager.h"

// Constructor
Queue::Queue(DataManager* dataMan)
    : queuePos(0, 0),
    queueSize(0, 0),
    dataManRef(dataMan),
    maxUnits(5),
    currentBarPercentage(0),
    currentUnitTrainTime(0),
    trainingUnit(false)
{}

void Queue::SetPositions(sf::Vector2f shopSize)
{
    sf::Vector2u windowSize = dataManRef->GetWindowSize();
    queuePos = sf::Vector2f(windowSize.x / 4, 0);
    queueSize = sf::Vector2f(windowSize.x - (windowSize.x / 4) - shopSize.x, 0);
    float barMargin = 5;
    queueBarPos = sf::Vector2f(queuePos.x + barMargin, queuePos.y + barMargin);
    queueBarSize = sf::Vector2f(queueSize.x - (barMargin * 2), 10);
    queueSlotsPos = sf::Vector2f(queueBarPos.x, queueBarPos.y + queueBarSize.y + barMargin);
}

void Queue::MoveQueue(int pos)
{
    sf::Vector2u windowSize = dataManRef->GetWindowSize();
    float barMargin = 5;
    queuePos = sf::Vector2f(windowSize.x / 4, 0);
    queueBarPos = sf::Vector2f(queuePos.x + barMargin + pos, queuePos.y + barMargin);
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

int Queue::GetUnitAmount()
{
    return unitQueue.size();
}

int Queue::GetMaxUnits()
{
    return maxUnits;
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
