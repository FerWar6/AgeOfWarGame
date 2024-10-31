#include "QueueSlot.h"
#include "UI/UIElements/Queue.h"

QueueSlot::QueueSlot(int id)
	: slotId(id),
	slotUnit(nullptr)
{}
bool QueueSlot::slotFilled()
{
	if (slotUnit == nullptr) {
		return false;
	}
	return true;
}

void QueueSlot::SetUnit(Unit* unit)
{
	DebugLn(slotFilled());
	unit = slotUnit;
	DebugLn(slotFilled());
}

Unit* QueueSlot::GetUnit()
{
	return slotUnit;
}
