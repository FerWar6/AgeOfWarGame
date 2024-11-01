#include "QueueSlot.h"
#include "UI/UIElements/Queue.h"

QueueSlot::QueueSlot(int id)
	: slotId(id),
	slotUnit(nullptr),
	slotFilled(false)
{}
bool QueueSlot::GetSlotFilled()
{
	return slotFilled;
}

void QueueSlot::SetUnit(Unit* unit)
{
	DebugLn(GetSlotFilled());
	unit = slotUnit;
	slotFilled = true;
	DebugLn(GetSlotFilled());
}

void QueueSlot::ClearUnit()
{
	slotUnit = nullptr;
	slotFilled = false;
}

Unit* QueueSlot::GetUnit()
{
	return slotUnit;
}
