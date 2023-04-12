#include "RangedCombatCondition.h"

RangedCombatEnemy::RangedCombatEnemy(const bool within_combat_range)
{
	m_name = "Ranged Combat Condition";
	SetIsWithinCombatRange(within_combat_range);
}

RangedCombatEnemy::~RangedCombatEnemy()
= default;

void RangedCombatEnemy::SetIsWithinCombatRange(const bool state)
{
	m_isWithinCombatRange = state;
}

bool RangedCombatEnemy::Condition()
{
	return m_isWithinCombatRange;
}
