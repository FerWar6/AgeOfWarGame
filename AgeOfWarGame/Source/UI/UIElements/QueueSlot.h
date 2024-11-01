#pragma once
#include "Engine/engine.h"

class Unit;
class QueueSlot
{
public:
	QueueSlot(int id);
	int slotId;
	bool GetSlotFilled();
	void SetUnit(Unit* unit);
	void ClearUnit();
	Unit* GetUnit();
private:
	Unit* slotUnit;
	bool slotFilled;
};