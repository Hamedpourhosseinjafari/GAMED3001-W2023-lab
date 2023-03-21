#include "CloseCombatCondition.h"

CloseCombatCondition::CloseCombatCondition(bool within_combat_range)
{
	m_name = "close combat condition";
	SetIsWhithinCombatRange(within_combat_range);
}

CloseCombatCondition::~CloseCombatCondition()
= default;
void CloseCombatCondition::SetIsWhithinCombatRange(const bool state)
{
	m_isWithinCombatRange = state;
}

bool CloseCombatCondition::Condition()
{
	return m_isWithinCombatRange;
}
