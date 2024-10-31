#pragma once
#include "Engine/engine.h"

class Unit;
class QueueSlot
{
public:
	QueueSlot(int id);
	int slotId;
	bool slotFilled();
	void SetUnit(Unit* unit);
	Unit* GetUnit();
private:
	Unit* slotUnit;

};