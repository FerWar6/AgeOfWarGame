#include "Queue.h"
#include "UI/UIRenderer.h"
#include "Objects/Unit.h"
#include "Data/DataManager.h"

Queue::Queue(sf::Vector2f pos, sf::Vector2f size, DataManager* dataMan)
    : queuePos(pos),
    queueSize(size),
    dataManRef(dataMan),
    trainingUnit(false)
{
    float barMargin = 5;
    queueBarPos = sf::Vector2f(pos.x + barMargin, pos.y + barMargin);
    queueBarSize = sf::Vector2f(size.x - (barMargin * 2), 10);

    queueSlotsPos = sf::Vector2f(queueBarPos.x, queueBarPos.y + queueBarSize.y + barMargin);

    CreateQueueSlots(queueSlotsPos);
}

void Queue::DrawQueue(sf::RenderWindow& window)
{
    //background
    sf::RectangleShape queue;
    queue.setSize(queueSize);
    queue.setPosition(queuePos);
    queue.setFillColor(sf::Color(70,70,70));
    window.draw(queue);
    //bar
    dataManRef->uiRenRef->DrawBar(queueBarSize, queueBarPos, QueueEmpty() ? 0 : currentBarPercentage, sf::Color::Red, false);
    //slots
    int filledSlots = 0;
    for (auto& slot : GetSlots()) if (slot.slotFilled()) filledSlots++;
    DrawQueueSlots(window, filledSlots);
}

void Queue::DrawQueueSlots(sf::RenderWindow& window, int filledSlots)
{
    int spaceBetweenSlots = 25;
    for (int i = 0; i < GetSlots().size(); ++i) {
        sf::Vector2f slotPos(queueSlotsPos.x + (spaceBetweenSlots * i), queueSlotsPos.y);
        if (i >= filledSlots) {
            window.draw(DrawSlot(false, slotPos));
        }
        else {
            window.draw(DrawSlot(true, slotPos));
        }
    }
}

void Queue::UpdateQueue()
{
    if (!QueueEmpty()) {
        if (!trainingUnit) {
            SetUnitToTrain();
            //get unit to train
        }
        else {
            UpdateTrainQueue();
            //update training timer
        }
    }
}

void Queue::UpdateTrainQueue()
{
    if (queueClock.getElapsedTime().asSeconds() >= currentUnitTrainTime) {
        dataManRef->MarkObjForAdd(GetFirstInQueue().GetUnit());
        //add unit to the game
        //move all units 1 position down
        trainingUnit = false;
    }
    CalculateBarPercentage(queueClock.getElapsedTime().asSeconds(), currentUnitTrainTime);
}

QueueSlot Queue::GetFirstInQueue()
{
    for (int i = 0; i < queueSlots.size(); ++i) {
        for (auto& slot : GetSlots()) {
            if (slot.slotId == i + 1 && slot.slotFilled()) return slot;
        }
    }
}


void Queue::SetUnitToTrain()
{
    //clear old unit and get the new firstInQueue unit
    GetFirstInQueue().SetUnit(nullptr);
    //move queue back by one
    currentUnitTrainTime = GetFirstInQueue().GetUnit()->GetTrainTime();
    queueClock.restart();
    trainingUnit = true;
}

void Queue::AddUnitToQueue(Unit* unit)
{
    DebugLn("start of add");
    FindEmptySlot().SetUnit(unit);
    int filledSlots = 0;
    for (auto& slot : GetSlots()) if (slot.slotFilled()) filledSlots++;
    DebugLn(filledSlots);
}

void Queue::CreateQueueSlots(sf::Vector2f startPos)
{
	int numberOfSlots = 5;
    for (int i = 0; i < numberOfSlots; ++i) {
        QueueSlot slot = QueueSlot(i + 1);
        queueSlots.push_back(slot);
    }
}

QueueSlot Queue::FindEmptySlot()
{
    for (int i = 0; i < queueSlots.size(); ++i) {
        for (auto& slot : GetSlots()) {
            if (slot.slotId == i + 1 && !slot.slotFilled()) return slot;
        }
    }
}

sf::RectangleShape Queue::DrawSlot(bool fill, sf::Vector2f pos)
{
    sf::RectangleShape slot;
    slot.setSize(sf::Vector2f(15, 15));
    slot.setPosition(pos);
    slot.setFillColor(fill ? sf::Color::Red : sf::Color::White);
    return slot;
}

std::vector<QueueSlot>& Queue::GetSlots()
{
    return queueSlots;
}

bool Queue::QueueEmpty()
{
    for (auto& slot : GetSlots()) {
        if(slot.slotFilled()) return false;
    }
    return true;
}

bool Queue::QueueFull()
{
    for (auto& slot : GetSlots()) {
        if (!slot.slotFilled()) return false;
    }
    return true;
}

void Queue::CalculateBarPercentage(float currentTime, float targetTime)
{
    float percentage = currentTime / targetTime;
    currentBarPercentage = percentage;
}
