#pragma once
#ifndef __CLOSE_COMBAT_CONDITION__
#define __CLOSE_COMBAT_CONDITION__

#include "ConditionNode.h"

class CloseCombatCondition : public ConditionNode
{
	CloseCombatCondition(bool within_combat_range = false);
	virtual ~CloseCombatCondition();

	//getters and setters
	void SetIsWhithinCombatRange(bool state);
	virtual bool Condition() override;;
private:
	bool m_isWithinCombatRange;
};
#endif
