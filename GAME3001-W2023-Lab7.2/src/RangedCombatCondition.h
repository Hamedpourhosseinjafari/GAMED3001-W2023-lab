#pragma once
#ifndef __RANGED_COMBAT_CONDITION__
#define __RANGED_COMBAT_CONDITION__

#include "ConditionNode.h"

class RangedCombatEnemy : public ConditionNode
{
public:
	RangedCombatEnemy(bool within_combat_range = false);
	virtual ~RangedCombatEnemy();

	// Setter
	void SetIsWithinCombatRange(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinCombatRange{};
};
#endif /* defined (__RANGED_COMBAT_CONDITION__) */